#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>

// int decay_pos(int pos_set, int decay_rate_ms, int decay_coef);
float pid_loop_step(float prev_pos, float new_pos, float proportional_coef, float integral_coef, float derivative_coef);

#endif