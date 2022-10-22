#include "neopixel-if.h"
#include "stdio.h"

#ifndef TEST
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "driver/rmt.h"
#include "led_strip.h"
#endif

static const char *TAG = "NEO-IF";

#define RMT_TX_CHANNEL RMT_CHANNEL_0

led_strip_t *init_led_strip(gpio_num_t gpio_num, uint32_t num_led)
{
    if(!num_led){
        return NULL;
    }

    ESP_LOGI(TAG,"Updating NUM led to %d",num_led);
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(gpio_num, RMT_TX_CHANNEL);
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