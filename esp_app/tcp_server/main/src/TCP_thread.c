#include"inc/TCP_thread.h"

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
#include "inc/UDP_thread.h"

static const char *TAG = "tcp";

bool UDP_sync = true;
bool SET_LED_CNT = false;

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
                case (led_code_sync):
                    UDP_sync = true;
                    break;
                case (num_led_read_num_led):
                    rx_buffer[0] = CONFIG_EXAMPLE_STRIP_LED_NUMBER;
                    for(int i = 0;i<5;i++){
                        send(sock, rx_buffer, 1, 0);
                    }
                    break;
                case (num_led_write_num_led):
                    wr_num_led_cnt =    (rx_buffer[1] << 0) +
                                        (rx_buffer[2] << 8) +
                                        (rx_buffer[3] << 16) +
                                        (rx_buffer[4] << 24);
                    wr_num_led = true;
                    
                    break;
                default :
                    ESP_LOGW(TAG, "Unknown TCP op code %x",*tcp_op_code);
                    break;
            }
            printf("\r\n");
        }
    } while (len > 0);
    ESP_LOGE(TAG,"TCP thread exiting");
}

void tcp_server_task(void *pvParameters)
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