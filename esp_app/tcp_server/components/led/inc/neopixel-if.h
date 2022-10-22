#ifndef _NEOPIXEL_IF_H_
#define _NEOPIXEL_IF_H_

#include <stdint.h>
#include <stdarg.h>


#ifndef TEST
#include "led_strip.h"
#include "driver/gpio.h"
#endif

led_strip_t *init_led_strip(gpio_num_t gpio_num, uint32_t num_led);

#endif