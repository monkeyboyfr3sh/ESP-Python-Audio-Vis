#ifndef _TCP_THREAD_H_
#define _TCP_THREAD_H_

#include "stdlib.h"
#include "stdbool.h"

#include <esp_system.h>
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

// TCP INFORMATION
#define TCP_PORT                    3333
#define KEEPALIVE_IDLE              5
#define KEEPALIVE_INTERVAL          5
#define KEEPALIVE_COUNT             3

extern bool UDP_sync;
extern bool SET_LED_CNT;

typedef struct {
    int socket_ID;

    char addr_str[128];
    int addr_family;
    int ip_protocol;
    int keepAlive;
    int keepIdle;
    int keepInterval;
    int keepCount;
    
    int listen_sock;
    struct sockaddr_storage dest_addr;
    struct sockaddr_in *dest_addr_ip4;
} socket_information_t;

typedef enum {
    tcp_task_fail = -1,
    tcp_task_ok = 0,
    tcp_task_memory_bad,
} tcp_task_err_t;

void tcp_server_task(void *pvParameters);
tcp_task_err_t setup_socket(socket_information_t *socket_info, int addr_family);
tcp_task_err_t init_sockaddr_storage(socket_information_t *socket_info);
tcp_task_err_t create_bind_socket(socket_information_t *socket_info);
tcp_task_err_t manage_socket(socket_information_t *socket_info);
tcp_task_err_t shutdown_socket(socket_information_t *socket_info);

#endif