#ifdef TEST

LCOV_EXCL_START;
#include "unity.h"
#include "fff.h"
DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(vTaskDelay, int);
FAKE_VALUE_FUNC(uint32_t,pdMS_TO_TICKS,uint32_t);
FAKE_VALUE_FUNC(uint32_t,xTaskGetTickCount);
LCOV_EXCL_STOP;


uint32_t tick_count = 0;

// DUT
#include "mock_typedefs.h"
#include "neopixel-if.h"

int test_count = 0;
void setUp(void)
{
    RESET_FAKE(vTaskDelay);
    RESET_FAKE(pdMS_TO_TICKS);
    RESET_FAKE(xTaskGetTickCount);
    test_count++;
}
void tearDown(void)
{
}

/*
    ##################################################
    ## Test PID
    ##################################################
*/

void test_init_led_strip_0(void)
{
    // float result;
    
    // float prev_pos = 0.0;
    // float new_pos = 1.0;

    // vTaskDelay_Expect(1);
    // init_led_strip(12, 45);

    // TEST_ASSERT_EQUAL(1, vTaskDelay_fake.call_count);   
    // TEST_ASSERT_EQUAL_FLOAT( 1.0, result );
}

#endif // TEST
