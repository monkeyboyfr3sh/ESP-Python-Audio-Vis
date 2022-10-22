#include "components/led/inc/neopixel-if.h"
#include "build/test/mocks/mock_typedefs.h"
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















void test_init_led_strip_0(void)

{

}
