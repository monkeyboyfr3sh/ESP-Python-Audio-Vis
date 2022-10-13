#include"inc/LED_thread.h"

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
#include "inc/utils.h"

#include "stdbool.h"
#include "utils.h"

static const char *TAG = "led";

bool led_on = true;
int wr_led_peak = 0;
int show_led_peak = 0;
uint32_t wr_led_peak_timestamp = 0;

bool wr_num_led = false;
int wr_num_led_cnt = 0;

led_strip_t *update_num_led(uint32_t num_led)
{
    ESP_LOGI(TAG,"Updating NUM led to %d",num_led);
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(GPIO_NUM_16, RMT_TX_CHANNEL);
    // set counter clock to 40MHz
    config.clk_div = 2;

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

    // install ws2812 driver
    led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(num_led, (led_strip_dev_t)config.channel);
    led_strip_t *strip = led_strip_new_rmt_ws2812(&strip_config);
    if (!strip) {
        ESP_LOGE(TAG, "install WS2812 driver failed");
    }

    // Clear LED strip (turn off all LEDs)
    ESP_ERROR_CHECK(strip->clear(strip, 100));
    ESP_ERROR_CHECK(strip->refresh(strip, 0));

    return strip;
}

void led_strip_task(void *pvParameters)
{
    uint32_t red = 0;
    uint32_t green = 0;
    uint32_t blue = 0;
    uint16_t hue = 0;
    uint16_t start_rgb = 0;
    int prev_pos = 0;

    // PID Settings
    const int Kc = 1.5;
    const float Tp = 1.25;
    const float Ti = 1.25;
    const float Td = 0.25;

    led_strip_t *strip = update_num_led(CONFIG_EXAMPLE_STRIP_LED_NUMBER);

    // Show simple rainbow chasing pattern
    ESP_LOGI(TAG, "LED Rainbow Chase Start");

    // uint32_t print_timestamp = xTaskGetTickCount();

    while(1){

        const int num_section = 5;
        const int section_size = CONFIG_EXAMPLE_STRIP_LED_NUMBER/num_section;

        for (int i = 0; i < num_section; i++) {
            
            // Build RGB values
            hue = start_rgb;
            hsv2rgb(hue, 100, 100, &red, &green, &blue);
            
            for (int j = 0; j < section_size; j += 1) {
                // Write RGB values to strip driver
                ESP_ERROR_CHECK(strip->set_pixel(strip, j+(section_size*i), red, green, blue));
            }
            // Flush RGB values to LEDs
            ESP_ERROR_CHECK(strip->refresh(strip, 0));
    
            start_rgb += 10;
        }

        vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));

    }

    while (true) {
        if(wr_num_led){
            strip->del(strip);
            strip = update_num_led(CONFIG_EXAMPLE_STRIP_LED_NUMBER);
            wr_num_led = false;
        }

        if(xTaskGetTickCount()-wr_led_peak_timestamp < pdMS_TO_TICKS(50)){
            // Calculate next LED peak, min should be 0
            show_led_peak =  (int)(Kc * pid_loop_step(prev_pos, wr_led_peak, Tp, Ti, Td));
            show_led_peak = (show_led_peak<0) ? 0 : show_led_peak;
        } else {
            // Applies natural decay to LEDs
            show_led_peak = decay_pos(prev_pos, 20, 2);
        }

        prev_pos = show_led_peak;

        if(led_on){
            for (int i = 0; i < 1; i++) {
                for (int j = i; j < CONFIG_EXAMPLE_STRIP_LED_NUMBER; j += 1) {
                    if(j < show_led_peak){
                        // Build RGB values
                        hue = j * 360 / show_led_peak + start_rgb;
                        hsv2rgb(hue, 100, 100, &red, &green, &blue);
                    } else {
                        red = 0; green = 0; blue = 0;
                    }
                    // Write RGB values to strip driver
                    ESP_ERROR_CHECK(strip->set_pixel(strip, j, red, green, blue));
                }
                // Flush RGB values to LEDs
                ESP_ERROR_CHECK(strip->refresh(strip, 0));
            }
            start_rgb += 60;
        }
        else {
            ESP_ERROR_CHECK(strip->clear(strip, 100));
            ESP_ERROR_CHECK(strip->refresh(strip, 0));
        }

        vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
    }
}
