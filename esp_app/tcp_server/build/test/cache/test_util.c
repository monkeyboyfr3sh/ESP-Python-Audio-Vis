#include "components/util/inc/utils.h"
#include "unit_testing/fff/fff.h"
#include "C:/Ruby25/lib/ruby/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




LCOV_EXCL_START;

 fff_globals_t fff; ;

typedef struct vTaskDelay_Fake { int arg0_val; int arg0_history[(50u)]; unsigned int call_count; unsigned int arg_history_len; unsigned int arg_histories_dropped; int custom_fake_seq_len; int custom_fake_seq_idx; void(*custom_fake)(int arg0); void(**custom_fake_seq)(int arg0); } vTaskDelay_Fake; extern vTaskDelay_Fake vTaskDelay_fake; void vTaskDelay_reset(void); void vTaskDelay(int arg0); vTaskDelay_Fake vTaskDelay_fake; void vTaskDelay(int arg0){ memcpy((void*)&vTaskDelay_fake.arg0_val, (void*)&arg0, sizeof(arg0));; if(vTaskDelay_fake.call_count < (50u)){ memcpy((void*)&vTaskDelay_fake.arg0_history[vTaskDelay_fake.call_count], (void*)&arg0, sizeof(arg0));; } else{ vTaskDelay_fake.arg_histories_dropped++; } vTaskDelay_fake.call_count++; if(fff.call_history_idx < (50u)) fff.call_history[fff.call_history_idx++] = (fff_function_t)vTaskDelay;; if (vTaskDelay_fake.custom_fake_seq_len){ if (vTaskDelay_fake.custom_fake_seq_idx < vTaskDelay_fake.custom_fake_seq_len){ vTaskDelay_fake.custom_fake_seq[vTaskDelay_fake.custom_fake_seq_idx++](arg0); } else{ vTaskDelay_fake.custom_fake_seq[vTaskDelay_fake.custom_fake_seq_len-1](arg0); } } if (vTaskDelay_fake.custom_fake){ vTaskDelay_fake.custom_fake(arg0); } } void vTaskDelay_reset(void){ memset(&vTaskDelay_fake, 0, sizeof(vTaskDelay_fake)); vTaskDelay_fake.arg_history_len = (50u); };

typedef struct pdMS_TO_TICKS_Fake { uint32_t arg0_val; uint32_t arg0_history[(50u)]; unsigned int call_count; unsigned int arg_history_len; unsigned int arg_histories_dropped; uint32_t return_val; int return_val_seq_len; int return_val_seq_idx; uint32_t * return_val_seq; uint32_t return_val_history[(50u)]; int custom_fake_seq_len; int custom_fake_seq_idx; uint32_t(*custom_fake)(uint32_t arg0); uint32_t(**custom_fake_seq)(uint32_t arg0); } pdMS_TO_TICKS_Fake; extern pdMS_TO_TICKS_Fake pdMS_TO_TICKS_fake; void pdMS_TO_TICKS_reset(void); uint32_t pdMS_TO_TICKS(uint32_t arg0); pdMS_TO_TICKS_Fake pdMS_TO_TICKS_fake; uint32_t pdMS_TO_TICKS(uint32_t arg0){ memcpy((void*)&pdMS_TO_TICKS_fake.arg0_val, (void*)&arg0, sizeof(arg0));; if(pdMS_TO_TICKS_fake.call_count < (50u)){ memcpy((void*)&pdMS_TO_TICKS_fake.arg0_history[pdMS_TO_TICKS_fake.call_count], (void*)&arg0, sizeof(arg0));; } else{ pdMS_TO_TICKS_fake.arg_histories_dropped++; } pdMS_TO_TICKS_fake.call_count++; if(fff.call_history_idx < (50u)) fff.call_history[fff.call_history_idx++] = (fff_function_t)pdMS_TO_TICKS;; if (pdMS_TO_TICKS_fake.custom_fake_seq_len){ if (pdMS_TO_TICKS_fake.custom_fake_seq_idx < pdMS_TO_TICKS_fake.custom_fake_seq_len){ uint32_t ret = pdMS_TO_TICKS_fake.custom_fake_seq[pdMS_TO_TICKS_fake.custom_fake_seq_idx++](arg0); if ((pdMS_TO_TICKS_fake.call_count - 1) < (50u)) memcpy((void *)&pdMS_TO_TICKS_fake.return_val_history[pdMS_TO_TICKS_fake.call_count - 1], (const void *) &ret, sizeof(ret));; return ret; } else{ uint32_t ret = pdMS_TO_TICKS_fake.custom_fake_seq[pdMS_TO_TICKS_fake.custom_fake_seq_len-1](arg0); if ((pdMS_TO_TICKS_fake.call_count - 1) < (50u)) memcpy((void *)&pdMS_TO_TICKS_fake.return_val_history[pdMS_TO_TICKS_fake.call_count - 1], (const void *) &ret, sizeof(ret));; return ret; return pdMS_TO_TICKS_fake.custom_fake_seq[pdMS_TO_TICKS_fake.custom_fake_seq_len-1](arg0); } } if (pdMS_TO_TICKS_fake.custom_fake){ uint32_t ret = pdMS_TO_TICKS_fake.custom_fake(arg0); if ((pdMS_TO_TICKS_fake.call_count - 1) < (50u)) memcpy((void *)&pdMS_TO_TICKS_fake.return_val_history[pdMS_TO_TICKS_fake.call_count - 1], (const void *) &ret, sizeof(ret));; return ret; return pdMS_TO_TICKS_fake.custom_fake(arg0); } if (pdMS_TO_TICKS_fake.return_val_seq_len){ if(pdMS_TO_TICKS_fake.return_val_seq_idx < pdMS_TO_TICKS_fake.return_val_seq_len) { if ((pdMS_TO_TICKS_fake.call_count - 1) < (50u)) memcpy((void *)&pdMS_TO_TICKS_fake.return_val_history[pdMS_TO_TICKS_fake.call_count - 1], (const void *) &pdMS_TO_TICKS_fake.return_val_seq[pdMS_TO_TICKS_fake.return_val_seq_idx], sizeof(pdMS_TO_TICKS_fake.return_val_seq[pdMS_TO_TICKS_fake.return_val_seq_idx])); return pdMS_TO_TICKS_fake.return_val_seq[pdMS_TO_TICKS_fake.return_val_seq_idx++]; } if ((pdMS_TO_TICKS_fake.call_count - 1) < (50u)) memcpy((void *)&pdMS_TO_TICKS_fake.return_val_history[pdMS_TO_TICKS_fake.call_count - 1], (const void *) &pdMS_TO_TICKS_fake.return_val_seq[pdMS_TO_TICKS_fake.return_val_seq_len-1], sizeof(pdMS_TO_TICKS_fake.return_val_seq[pdMS_TO_TICKS_fake.return_val_seq_len-1])); return pdMS_TO_TICKS_fake.return_val_seq[pdMS_TO_TICKS_fake.return_val_seq_len-1]; } if ((pdMS_TO_TICKS_fake.call_count - 1) < (50u)) memcpy((void *)&pdMS_TO_TICKS_fake.return_val_history[pdMS_TO_TICKS_fake.call_count - 1], (const void *) &pdMS_TO_TICKS_fake.return_val, sizeof(pdMS_TO_TICKS_fake.return_val)); return pdMS_TO_TICKS_fake.return_val; } void pdMS_TO_TICKS_reset(void){ memset(&pdMS_TO_TICKS_fake, 0, sizeof(pdMS_TO_TICKS_fake)); pdMS_TO_TICKS_fake.arg_history_len = (50u); };

typedef struct xTaskGetTickCount_Fake { unsigned int call_count; unsigned int arg_history_len; unsigned int arg_histories_dropped; uint32_t return_val; int return_val_seq_len; int return_val_seq_idx; uint32_t * return_val_seq; uint32_t return_val_history[(50u)]; int custom_fake_seq_len; int custom_fake_seq_idx; uint32_t(*custom_fake)(void); uint32_t(**custom_fake_seq)(void); } xTaskGetTickCount_Fake; extern xTaskGetTickCount_Fake xTaskGetTickCount_fake; void xTaskGetTickCount_reset(void); uint32_t xTaskGetTickCount(void); xTaskGetTickCount_Fake xTaskGetTickCount_fake; uint32_t xTaskGetTickCount(void){ if(xTaskGetTickCount_fake.call_count < (50u)){ } else{ xTaskGetTickCount_fake.arg_histories_dropped++; } xTaskGetTickCount_fake.call_count++; if(fff.call_history_idx < (50u)) fff.call_history[fff.call_history_idx++] = (fff_function_t)xTaskGetTickCount;; if (xTaskGetTickCount_fake.custom_fake_seq_len){ if (xTaskGetTickCount_fake.custom_fake_seq_idx < xTaskGetTickCount_fake.custom_fake_seq_len){ uint32_t ret = xTaskGetTickCount_fake.custom_fake_seq[xTaskGetTickCount_fake.custom_fake_seq_idx++](); if ((xTaskGetTickCount_fake.call_count - 1) < (50u)) memcpy((void *)&xTaskGetTickCount_fake.return_val_history[xTaskGetTickCount_fake.call_count - 1], (const void *) &ret, sizeof(ret));; return ret; } else{ uint32_t ret = xTaskGetTickCount_fake.custom_fake_seq[xTaskGetTickCount_fake.custom_fake_seq_len-1](); if ((xTaskGetTickCount_fake.call_count - 1) < (50u)) memcpy((void *)&xTaskGetTickCount_fake.return_val_history[xTaskGetTickCount_fake.call_count - 1], (const void *) &ret, sizeof(ret));; return ret; return xTaskGetTickCount_fake.custom_fake_seq[xTaskGetTickCount_fake.custom_fake_seq_len-1](); } } if (xTaskGetTickCount_fake.custom_fake){ uint32_t ret = xTaskGetTickCount_fake.custom_fake(); if ((xTaskGetTickCount_fake.call_count - 1) < (50u)) memcpy((void *)&xTaskGetTickCount_fake.return_val_history[xTaskGetTickCount_fake.call_count - 1], (const void *) &ret, sizeof(ret));; return ret; return xTaskGetTickCount_fake.custom_fake(); } if (xTaskGetTickCount_fake.return_val_seq_len){ if(xTaskGetTickCount_fake.return_val_seq_idx < xTaskGetTickCount_fake.return_val_seq_len) { if ((xTaskGetTickCount_fake.call_count - 1) < (50u)) memcpy((void *)&xTaskGetTickCount_fake.return_val_history[xTaskGetTickCount_fake.call_count - 1], (const void *) &xTaskGetTickCount_fake.return_val_seq[xTaskGetTickCount_fake.return_val_seq_idx], sizeof(xTaskGetTickCount_fake.return_val_seq[xTaskGetTickCount_fake.return_val_seq_idx])); return xTaskGetTickCount_fake.return_val_seq[xTaskGetTickCount_fake.return_val_seq_idx++]; } if ((xTaskGetTickCount_fake.call_count - 1) < (50u)) memcpy((void *)&xTaskGetTickCount_fake.return_val_history[xTaskGetTickCount_fake.call_count - 1], (const void *) &xTaskGetTickCount_fake.return_val_seq[xTaskGetTickCount_fake.return_val_seq_len-1], sizeof(xTaskGetTickCount_fake.return_val_seq[xTaskGetTickCount_fake.return_val_seq_len-1])); return xTaskGetTickCount_fake.return_val_seq[xTaskGetTickCount_fake.return_val_seq_len-1]; } if ((xTaskGetTickCount_fake.call_count - 1) < (50u)) memcpy((void *)&xTaskGetTickCount_fake.return_val_history[xTaskGetTickCount_fake.call_count - 1], (const void *) &xTaskGetTickCount_fake.return_val, sizeof(xTaskGetTickCount_fake.return_val)); return xTaskGetTickCount_fake.return_val; } void xTaskGetTickCount_reset(void){ memset(&xTaskGetTickCount_fake, 0, sizeof(xTaskGetTickCount_fake)); xTaskGetTickCount_fake.arg_history_len = (50u); };

LCOV_EXCL_STOP;



uint32_t tick_count = 0;







int test_count = 0;

void setUp(void)

{

    { vTaskDelay_reset(); };

    { pdMS_TO_TICKS_reset(); };

    { xTaskGetTickCount_reset(); };

    test_count++;

}

void tearDown(void)

{

}















void test_pid_0(void)

{

    float result;



    float prev_pos = 0.0;

    float new_pos = 1.0;





    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((vTaskDelay_fake.call_count)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_INT);

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(46)));

}



void test_pid_1(void)

{

    float result;



    float prev_pos = 0.0;

    float new_pos = -1.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(58)));

}



void test_pid_2(void)

{

    float result;



    float prev_pos = -1.0;

    float new_pos = 0.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(70)));

}



void test_pid_3(void)

{

    float result;



    float prev_pos = -1.0;

    float new_pos = -1.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(82)));

}



void test_pid_4(void)

{

    float result;



    float prev_pos = 0.0;

    float new_pos = 0.0;







    for(int i = 0;i<100;i++){





        prev_pos = new_pos;

        new_pos++;



        result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



        UnityAssertEqualNumber((UNITY_INT)((i+1)), (UNITY_INT)((vTaskDelay_fake.call_count)), (

       ((void *)0)

       ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);

        UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((new_pos)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((new_pos))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

       ((void *)0)

       )), (UNITY_UINT)((UNITY_UINT)(103)));

    }



}















void test_hsv2rgb_0(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(0, 100, 100, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((255)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_1(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(240, 100, 100, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(138), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(139), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((255)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_2(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(180, 100, 100, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((255)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((255)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_3(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(120, 100, 50, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(168), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((127)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(169), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(171), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_4(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(67, 0, 75, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((191)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(183), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((191)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(184), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((191)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(185), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(186), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_5(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(42, 96, 90, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((229)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(198), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((163)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(199), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((9)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(200), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(201), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_6(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(300, 23, 64, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((163)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(213), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((125)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(214), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((163)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(215), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(216), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_7(void)

{



    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(300, 23, 64, (uint32_t *)0, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(227), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_8(void)

{



    uint32_t r;

    uint32_t b;



    int rval = hsv2rgb(300, 23, 64, &r, (uint32_t *)0, &b);



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(238), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_9(void)

{



    uint32_t r;

    uint32_t g;



    int rval = hsv2rgb(300, 23, 64, &r, &g, (uint32_t *)0);



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(249), UNITY_DISPLAY_STYLE_INT);

}

uint32_t update_tick(void)

{

    return tick_count;

}



uint32_t tick_to_ms(uint32_t input)

{

    return input;

}



uint32_t decay_unit(uint32_t init_val, int num_iter, int decay_rate, int decay_coef)

{

    uint32_t result;



    tick_count = 0;

    result = init_val;

    for(int i = 0;i<num_iter;i++){

        result = decay_pos(result, decay_rate, decay_coef);

        printf("Result: %u\n",result);

        tick_count++;

    }

    return result;

}

void test_decay_pos_0(void)

{

    xTaskGetTickCount_fake.custom_fake = update_tick;

    pdMS_TO_TICKS_fake.custom_fake = tick_to_ms;



    uint32_t decay_val = 100;

    decay_val = decay_unit(decay_val, 10, 5, 2);

    decay_val = decay_unit(decay_val, 20, 5, 2);

    decay_val = decay_unit(decay_val, 2, 5, 2);



    UnityAssertEqualNumber((UNITY_INT)((88)), (UNITY_INT)((decay_val)), (

   ((void *)0)

   ), (UNITY_UINT)(292), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((38)), (UNITY_INT)((xTaskGetTickCount_fake.call_count)), (

   ((void *)0)

   ), (UNITY_UINT)(293), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((32)), (UNITY_INT)((pdMS_TO_TICKS_fake.call_count)), (

   ((void *)0)

   ), (UNITY_UINT)(294), UNITY_DISPLAY_STYLE_INT);

}



void test_decay_pos_1(void)

{

    xTaskGetTickCount_fake.custom_fake = update_tick;

    pdMS_TO_TICKS_fake.custom_fake = tick_to_ms;



    uint32_t decay_val = 0;

    decay_val = decay_unit(decay_val, 20, 8, 8);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((decay_val)), (

   ((void *)0)

   ), (UNITY_UINT)(305), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((xTaskGetTickCount_fake.call_count)), (

   ((void *)0)

   ), (UNITY_UINT)(306), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((pdMS_TO_TICKS_fake.call_count)), (

   ((void *)0)

   ), (UNITY_UINT)(307), UNITY_DISPLAY_STYLE_INT);

}
