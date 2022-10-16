#include"TCP_thread.h"

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

#include "driver/gpio.h"

#include "driver/rmt.h"
#include "led_strip.h"

#include "stdbool.h"
#include "stdio.h"

static const char *TAG = "tcp";

bool UDP_sync = true;
bool SET_LED_CNT = false;

#ifndef TEST
#include "LED_thread.h"
#include "UDP_thread.h"

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

tcp_task_err_t init_sockaddr_storage(socket_information_t *socket_info)
{
    tcp_task_err_t rval = tcp_task_fail;
    if (socket_info->addr_family == AF_INET) {
        socket_info->dest_addr_ip4 = (struct sockaddr_in *)&(socket_info->dest_addr);
        socket_info->dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        socket_info->dest_addr_ip4->sin_family = AF_INET;
        socket_info->dest_addr_ip4->sin_port = htons(TCP_PORT);
        socket_info->ip_protocol = IPPROTO_IP;
        rval = tcp_task_ok;
    }

    return rval;
}

tcp_task_err_t create_bind_socket(socket_information_t *socket_info)
{
    // First create socket
    socket_info->listen_sock = socket(socket_info->addr_family, SOCK_STREAM, socket_info->ip_protocol);
    if (socket_info->listen_sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        return tcp_task_fail;
    }
    int opt = 1;
    setsockopt(socket_info->listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    ESP_LOGI(TAG, "Socket created");

    // Now bind the socket
    int err = bind(socket_info->listen_sock, (struct sockaddr *)&(socket_info->dest_addr), sizeof(socket_info->dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", socket_info->addr_family);
        return tcp_task_fail;
    }
    ESP_LOGI(TAG, "Socket bound, port %d", TCP_PORT);

    err = listen(socket_info->listen_sock, 1);
    if (err != 0) {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        return tcp_task_fail;
    }

    return tcp_task_ok;
}

tcp_task_err_t manage_socket(socket_information_t *socket_info)
{
    while (1) {

        ESP_LOGI(TAG, "Socket listening");

        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t addr_len = sizeof(source_addr);
        int sock = accept(socket_info->listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            return tcp_task_fail;
        }

        // Set tcp keepalive option
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &(socket_info->keepAlive), sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &(socket_info->keepIdle), sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &(socket_info->keepInterval), sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &(socket_info->keepCount), sizeof(int));
        // Convert ip address to string
        if (source_addr.ss_family == PF_INET) {
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, (socket_info->addr_str), sizeof(socket_info->addr_str) - 1);
        }
        ESP_LOGI(TAG, "Socket accepted ip address: %s", socket_info->addr_str);

        // Receive data via TCP on this socket
        do_retransmit(sock);
    }
}

tcp_task_err_t shutdown_socket(socket_information_t *socket_info)
{
    close(socket_info->listen_sock);
    return tcp_task_ok;
}

#endif

tcp_task_err_t setup_socket(socket_information_t *socket_info, int addr_family)
{
    // printf("Setting up socket %d\n",socket_info->socket_ID);
    socket_info->addr_family = addr_family;
    socket_info->ip_protocol = 0;
    socket_info->keepAlive = 1;
    socket_info->keepIdle = KEEPALIVE_IDLE;
    socket_info->keepInterval = KEEPALIVE_INTERVAL;
    socket_info->keepCount = KEEPALIVE_COUNT;

    // Try setting up socket storage
    tcp_task_err_t init_err = init_sockaddr_storage( socket_info );
    if(init_err != tcp_task_ok) {
        return init_err;
    }

    tcp_task_err_t create_bind_err = create_bind_socket ( socket_info );
    if(create_bind_err != tcp_task_ok) {
        return create_bind_err;
    }

    return tcp_task_ok;
}

void tcp_server_task(void *pvParameters)
{
    socket_information_t my_sock = {
        .socket_ID = 0,
    };

    // Setup socket
    tcp_task_err_t setup_err =  setup_socket( &my_sock, (int)pvParameters );
    
    // Only manage the socket if success in setup
    if(setup_err == tcp_task_ok){

        // Manage the socket
        tcp_task_err_t management_err = manage_socket( &my_sock );
    }

    // Shutdown socket on exit
    shutdown_socket( &my_sock );

    // Delete thread
    vTaskDelete(NULL);
}