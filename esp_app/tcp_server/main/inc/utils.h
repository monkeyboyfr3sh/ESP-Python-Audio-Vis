#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>
#include <stdarg.h>

#ifndef TEST
int decay_pos(int pos_set, int decay_rate_ms, int decay_coef);
#endif

float pid_loop_step(float prev_pos, float new_pos, float proportional_coef, float integral_coef, float derivative_coef);
void hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b);

#endif