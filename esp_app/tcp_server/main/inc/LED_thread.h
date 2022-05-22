#ifndef _LED_THREAD_H_
#define _LED_THREAD_H_

#include "stdlib.h"
#include "stdbool.h"

#define RMT_TX_CHANNEL RMT_CHANNEL_0

#define EXAMPLE_CHASE_SPEED_MS          (50)
#define CONFIG_EXAMPLE_STRIP_LED_NUMBER (124)

extern bool led_on;
extern uint32_t led_peak;

typedef enum {
    led_code_off = 0,
    led_code_on,
    led_code_pos,
} led_code_t;

void led_strip_task(void *pvParameters);

#endif