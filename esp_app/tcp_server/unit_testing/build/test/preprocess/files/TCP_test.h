#include "test/esp-idf-mock/esp_system.h"
#include "../main/inc/TCP_thread.h"










tcp_task_err_t init_sockaddr_storage(socket_information_t *socket_info);

tcp_task_err_t create_bind_socket(socket_information_t *socket_info);

tcp_task_err_t manage_socket(socket_information_t *socket_info);

tcp_task_err_t shutdown_socket(socket_information_t *socket_info);
