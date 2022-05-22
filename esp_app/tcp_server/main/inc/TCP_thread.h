#ifndef _TCP_THREAD_H_
#define _TCP_THREAD_H_

#include "stdlib.h"
#include "stdbool.h"

// TCP INFORMATION
#define TCP_PORT                    3333
#define KEEPALIVE_IDLE              5
#define KEEPALIVE_INTERVAL          5
#define KEEPALIVE_COUNT             3

void tcp_server_task(void *pvParameters);

#endif