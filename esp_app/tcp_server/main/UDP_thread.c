#include"inc/UDP_thread.h"

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

static const char *TAG = "udp";

static const char *payload = "Message from ESP32 ";

// UDP information
char rx_buffer[128];
char host_ip[] = HOST_IP_ADDR;
int addr_family = AF_INET;
int ip_protocol = IPPROTO_IP;
int sock = -1;

void update_socket(void);

void udp_write_hello(int sock)
{
    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(UDP_PORT);
    // Send first packet to listening port
    int err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
    }
    ESP_LOGI(TAG, "Message sent");
}

void udp_hello_client_task(void *pvParameters)
{
    static uint32_t hello_timestamp = 0;

    while(1){
        if (sock != -1) {
            if( (xTaskGetTickCount()-hello_timestamp) > pdMS_TO_TICKS(UDP_HELLO_PERIOD_MS)){
                hello_timestamp = xTaskGetTickCount();
                udp_write_hello(sock);
            }
        } 
        vTaskDelay(1);
    }
}

void udp_streaming_client_task(void *pvParameters)
{
    char *udp_op_code = &rx_buffer[0];

    while (1) {
        // Create socket
        sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        }
        ESP_LOGI(TAG, "Socket created, sending to %s:%d", HOST_IP_ADDR, UDP_PORT);
        
        udp_write_hello(sock);

        // Now begin receiving data stream
        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t socklen = sizeof(source_addr);

        uint32_t hello_timestamp = xTaskGetTickCount();
        while (1) {

            // Delete port and resync
            if(UDP_sync){
                UDP_sync = false;
                ESP_LOGI(TAG,"UDP sync request!");
                break;
            }

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

                        led_peak =  (rx_buffer[1] << 0) +
                                    (rx_buffer[2] << 8) +
                                    (rx_buffer[3] << 16) +
                                    (rx_buffer[4] << 24);
                        if(led_peak > CONFIG_EXAMPLE_STRIP_LED_NUMBER){
                            led_peak = CONFIG_EXAMPLE_STRIP_LED_NUMBER;
                        }

                        break;
                    default :
                        ESP_LOGW(TAG, "Unknown UDP op code %x",*udp_op_code);
                        esp_log_buffer_hex(TAG,rx_buffer,len);
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