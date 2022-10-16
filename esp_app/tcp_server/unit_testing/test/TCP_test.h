#ifndef _MOCK_TCP_TEST_H_
#define _MOCK_TCP_TEST_H_

#include "TCP_thread.h"
#include "esp_system.h"

tcp_task_err_t init_sockaddr_storage(socket_information_t *socket_info);
tcp_task_err_t create_bind_socket(socket_information_t *socket_info);
tcp_task_err_t manage_socket(socket_information_t *socket_info);
tcp_task_err_t shutdown_socket(socket_information_t *socket_info);

#endif