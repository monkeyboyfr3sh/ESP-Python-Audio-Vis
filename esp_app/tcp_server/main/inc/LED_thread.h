#ifndef _LED_THREAD_H_
#define _LED_THREAD_H_

#include "stdlib.h"
#include "stdbool.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "led_strip.h"

#define RMT_TX_CHANNEL RMT_CHANNEL_0

#define EXAMPLE_CHASE_SPEED_MS          (10)
#define CONFIG_EXAMPLE_STRIP_LED_NUMBER (256)

extern bool led_on;
extern int wr_led_peak;
extern uint32_t wr_led_peak_timestamp;

extern bool wr_num_led;
extern int wr_num_led_cnt;

typedef enum {
    led_code_off = 0,
    led_code_on,
    led_code_pos,
    led_code_sync,
    num_led_read_num_led,
    num_led_write_num_led,
} led_code_t;

led_strip_t *update_num_led(uint32_t num_led);
void led_strip_task(void *pvParameters);

#endif