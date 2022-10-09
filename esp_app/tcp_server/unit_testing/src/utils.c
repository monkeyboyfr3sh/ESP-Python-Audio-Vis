#include "utils.h"
#include "stdio.h"

// #ifndef TEST
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_system.h"
// #include "esp_wifi.h"
// #include "esp_event.h"
// #include "esp_log.h"
// #endif

// int decay_pos(int pos_set, int decay_rate_ms, int decay_coef)
// {
//     static uint32_t timestamp = 0;
//     static int pos;

//     pos = pos_set; 
//     if(pos){
//         if( (xTaskGetTickCount()-timestamp) > pdMS_TO_TICKS(decay_rate_ms) ){
//             timestamp = xTaskGetTickCount();
//             pos -= (pos > decay_coef) ? decay_coef : pos;
//         }
//     }

//     return pos;
// }

float pid_loop_step(float prev_pos, float new_pos, float proportional_coef, float integral_coef, float derivative_coef)
{
    if((prev_pos<0)||(new_pos<0)){
        return (float)-1.0;
    }

    // Calaculate feedback values
    float p = (proportional_coef * ( (float)new_pos) );
    float i = (integral_coef * ( (float)prev_pos) );
    float d = (derivative_coef * ((float)(new_pos-prev_pos)) );
    // Return next step value
    return p+i+d;
}