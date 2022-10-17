#include "utils.h"
#include "stdio.h"

#ifndef TEST
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#endif

int decay_pos(int pos_set, int decay_rate_ms, int decay_coef)
{
    static uint32_t timestamp = 0;
    static int pos;

    pos = pos_set; 
    if(pos){
        if( (xTaskGetTickCount()-timestamp) >= pdMS_TO_TICKS(decay_rate_ms) ){
            timestamp = xTaskGetTickCount();
            pos -= (pos > decay_coef) ? decay_coef : pos;
        }
    }
    
    return pos;
}

float pid_loop_step(float prev_pos, float new_pos, float proportional_coef, float integral_coef, float derivative_coef)
{
    if((prev_pos<0)||(new_pos<0)){
        return (float)-1.0;
    }

    // Calaculate feedback values
    float p = (proportional_coef * ( (float)new_pos) );
    float i = (integral_coef * ( (float)prev_pos) );
    float d = (derivative_coef * ((float)(new_pos-prev_pos)) );

    vTaskDelay(1);

    // Return next step value
    return p+i+d;
}

int hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b)
{
    // Verify pointers are okay
    if(!r || !g || !b)
    {
        return -1;
    }

    h %= 360; // h -> [0,360]
    uint8_t i = h/60;
    float s_percent  = (s%101) / 100.00f;
    float v_percent  = (v%101) / 100.00f;
    float c = v_percent*s_percent;
    float mod_val = ((float)h/60.0);
    mod_val = (mod_val < 1) ? mod_val : ((int)mod_val%2); 
    float temp = mod_val - 1;
    temp = temp<0 ? -temp : temp;
    float x = c*(1-temp);
    float m = v_percent-c; 

    // printf("h: %u s: %u(%f) v: %u(%f) c: %f x: %f m: %f i: %u\n",h,s,s_percent,v,v_percent,c,x,m,i);
    // printf("i: %u\n",i);

    switch (i) {
    case 0:
        *r = (uint32_t)( (c+m)*255 );
        *g = (uint32_t)( (x+m)*255 );
        *b = (uint32_t)( m*255 );
        break;
    case 1:
        *r = (uint32_t)( (x+m)*255 );
        *g = (uint32_t)( (c+m)*255 );
        *b = (uint32_t)( m*255 );
        break;
    case 2:
        *r = (uint32_t)( m*255 );
        *g = (uint32_t)( (c+m)*255 );
        *b = (uint32_t)( (x+m)*255 );
        break;
    case 3:
        *r = (uint32_t)( m*255 );
        *g = (uint32_t)( (x+m)*255 );
        *b = (uint32_t)( (c+m)*255 );
        break;
    case 4:
        *r = (uint32_t)( (x+m)*255 );
        *g = (uint32_t)( m*255 );
        *b = (uint32_t)( (c+m)*255 );
        break;
    default:
    case 5:
        *r = (uint32_t)( (c+m)*255 );
        *g = (uint32_t)( m*255 );
        *b = (uint32_t)( (x+m)*255 );
        break;
    }

    return 0;
}