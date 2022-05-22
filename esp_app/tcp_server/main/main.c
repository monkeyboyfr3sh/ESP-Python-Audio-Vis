#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "driver/gpio.h"

#include "driver/rmt.h"
#include "led_strip.h"

#include "stdbool.h"

#include "inc/LED_thread.h"
#include "inc/TCP_thread.h"
#include "inc/UDP_thread.h"

static const char *TAG = "audio-vis";

static void do_retransmit(const int sock)
{
    int len;
    char rx_buffer[128];
    uint8_t level = 0;
    char *tcp_op_code = &rx_buffer[0];

    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            // ESP_LOGI(TAG, "Received %d bytes: %s", len, rx_buffer);
            ESP_LOGI(TAG, "Received %d bytes via:", len);
            esp_log_buffer_hex(TAG,rx_buffer,len);

            ESP_LOGI(TAG, "OPCODE:%x",*tcp_op_code);
            switch(*tcp_op_code){
                case (led_code_off):
                    ESP_LOGI(TAG, "Turing LEDs OFF!");
                    led_on = false;
                    break;
                case (led_code_on):
                    ESP_LOGI(TAG, "Turing LEDs ON!");
                    led_on = true;
                    break;
                case (led_code_pos):
                    // led_on = true;
                    led_peak =  (rx_buffer[1] << 0) +
                                (rx_buffer[2] << 8) +
                                (rx_buffer[3] << 16) +
                                (rx_buffer[4] << 24);
                    if(led_peak > CONFIG_EXAMPLE_STRIP_LED_NUMBER){
                        led_peak = CONFIG_EXAMPLE_STRIP_LED_NUMBER;
                    }
                    ESP_LOGI(TAG, "Setting peak LED to %d!",led_peak);
                    break;
                default :
                    ESP_LOGW(TAG, "Unknown TCP op code %x",*tcp_op_code);
                    break;
            }
        }
    } while (len > 0);
}

static void tcp_server_task(void *pvParameters)
{
    char addr_str[128];
    int addr_family = (int)pvParameters;
    int ip_protocol = 0;
    int keepAlive = 1;
    int keepIdle = KEEPALIVE_IDLE;
    int keepInterval = KEEPALIVE_INTERVAL;
    int keepCount = KEEPALIVE_COUNT;
    struct sockaddr_storage dest_addr;

    if (addr_family == AF_INET) {
        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(TCP_PORT);
        ip_protocol = IPPROTO_IP;
    }

    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (listen_sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ESP_LOGI(TAG, "Socket created");

    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", addr_family);
        goto CLEAN_UP;
    }
    ESP_LOGI(TAG, "Socket bound, port %d", TCP_PORT);

    err = listen(listen_sock, 1);
    if (err != 0) {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        goto CLEAN_UP;
    }

    while (1) {

        ESP_LOGI(TAG, "Socket listening");

        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t addr_len = sizeof(source_addr);
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        // Set tcp keepalive option
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));
        // Convert ip address to string
        if (source_addr.ss_family == PF_INET) {
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
        }
        ESP_LOGI(TAG, "Socket accepted ip address: %s", addr_str);

        do_retransmit(sock);

        shutdown(sock, 0);
        close(sock);
    }

CLEAN_UP:
    close(listen_sock);
    vTaskDelete(NULL);
}

static const char *payload = "Message from ESP32 ";
static void udp_client_task(void *pvParameters)
{
    char rx_buffer[128];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;
    char *udp_op_code = &rx_buffer[0];

    while (1) {
        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(UDP_PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created, sending to %s:%d", HOST_IP_ADDR, UDP_PORT);

        int err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err < 0) {
            ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Message sent");

        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t socklen = sizeof(source_addr);

        while (1) {
            int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);

            // Error occurred during receiving
            if (len < 0) {
                ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
                break;
            }
            // Data received
            else {
                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                // ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
                // esp_log_buffer_hex(TAG,rx_buffer,len);

                // ESP_LOGI(TAG, "OPCODE:%x",*udp_op_code);
                switch(*udp_op_code){
                    case (led_code_pos):
                        // led_on = true;
                        led_peak =  (rx_buffer[1] << 0) +
                                    (rx_buffer[2] << 8) +
                                    (rx_buffer[3] << 16) +
                                    (rx_buffer[4] << 24);
                        if(led_peak > CONFIG_EXAMPLE_STRIP_LED_NUMBER){
                            led_peak = CONFIG_EXAMPLE_STRIP_LED_NUMBER;
                        }
                        // ESP_LOGI(TAG, "Setting peak LED to %d!",led_peak);
                        break;
                    default :
                        ESP_LOGW(TAG, "Unknown UDP op code %x",*udp_op_code);
                        break;
                }

            }
        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET, 5, NULL);
    xTaskCreate(udp_client_task, "udp_client", 4096, (void*)AF_INET, 5, NULL);
    xTaskCreate(led_strip_task, "led_task", 4096, (void*)AF_INET, 5, NULL);
}
