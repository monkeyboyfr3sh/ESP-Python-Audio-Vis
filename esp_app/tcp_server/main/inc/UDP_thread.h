#ifndef _UDP_THREAD_H_
#define _UDP_THREAD_H_

#include "stdlib.h"
#include "stdbool.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"

// UDP INFORMATION
#define HOST_IP_ADDR "192.168.0.160"
#define UDP_PORT 20001
#define UDP_HELLO_PERIOD_MS 5000

void udp_streaming_client_task(void *pvParameters);
void udp_hello_client_task(void *pvParameters);

#endif