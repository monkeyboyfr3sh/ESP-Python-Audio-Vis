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

void app_main(void)
{
    // ESP_ERROR_CHECK(nvs_flash_init());
    // ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());

    // /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
    //  * Read "Establishing Wi-Fi or Ethernet Connection" section in
    //  * examples/protocols/README.md for more information about this function.
    //  */
    // ESP_ERROR_CHECK(example_connect());

    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET, 5, NULL);
    // xTaskCreate(udp_streaming_client_task, "udp_streaming_client", 4096, (void*)AF_INET, 5, NULL);
    // xTaskCreate(udp_hello_client_task, "udp_hello_client", 4096, (void*)AF_INET, 5, NULL);
    xTaskCreate(led_strip_task, "led_task", 2048, (void*)AF_INET, 5, NULL);
}
