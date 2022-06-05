#include "inc\utils.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

int decay_pos(int pos_set, int decay_rate_ms, int decay_coef)
{
    static uint32_t timestamp = 0;
    static int pos;

    pos = pos_set; 
    if(pos){
        if( (xTaskGetTickCount()-timestamp) > pdMS_TO_TICKS(decay_rate_ms) ){
            timestamp = xTaskGetTickCount();
            pos -= (pos > decay_coef) ? decay_coef : pos;
        }
    }

    return pos;
}

int proportional_pos(int prev_pos,float proportional_coef)
{
    return (proportional_coef * ( (float)prev_pos) ); 
}

int integral_pos(int prev_pos,float integral_coef)
{
    return (integral_coef * ( (float)prev_pos) ); 
}

int derivative_pos(int error,float derivative_coef)
{
    return (derivative_coef * ( (float)error) ); 
}

// uint32_t integral_pos(uint32_t wr_pos,uint32_t prev_pos,float integral_coef)
// {
//     int delta = (prev_pos - wr_pos);
//     uint32_t return_pos  = (uint32_t)(prev_pos - (derivative_coef * ( (float)delta) ) );

//     return return_pos; 
// }
