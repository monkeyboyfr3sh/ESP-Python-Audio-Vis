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
#include "utils.h"

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

void test_pid_0(void)
{
    float result;
    
    float prev_pos = 0.0;
    float new_pos = 1.0;

    // vTaskDelay_Expect(1);
    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);

    TEST_ASSERT_EQUAL(1, vTaskDelay_fake.call_count);   
    TEST_ASSERT_EQUAL_FLOAT( 1.0, result );
}

void test_pid_1(void)
{
    float result;
    
    float prev_pos = 0.0;
    float new_pos = -1.0;

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT( -1.0, result );
}

void test_pid_2(void)
{
    float result;
    
    float prev_pos = -1.0;
    float new_pos = 0.0;

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT( -1.0, result );
}

void test_pid_3(void)
{
    float result;
    
    float prev_pos = -1.0;
    float new_pos = -1.0;

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT( -1.0, result );
}

void test_pid_4(void)
{
    float result;
    
    float prev_pos = 0.0;
    float new_pos = 0.0;

    

    for(int i = 0;i<100;i++){

        // Update step
        prev_pos = new_pos;
        new_pos++;
        // Get next step
        result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
        
        TEST_ASSERT_EQUAL(i+1, vTaskDelay_fake.call_count);
        TEST_ASSERT_EQUAL_FLOAT( new_pos, result );
    }
    
}

/*
    ##################################################
    ## Test hsv2rgb
    ##################################################
*/

void test_hsv2rgb_0(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    int rval = hsv2rgb(0, 100, 100, &r, &g, &b);

    TEST_ASSERT_EQUAL_UINT32( 255, r );
    TEST_ASSERT_EQUAL_UINT32( 0, g );
    TEST_ASSERT_EQUAL_UINT32( 0, b );
    TEST_ASSERT_EQUAL_INT( 0, rval );
}

void test_hsv2rgb_1(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    int rval = hsv2rgb(240, 100, 100, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 0, r );
    TEST_ASSERT_EQUAL_UINT32( 0, g );
    TEST_ASSERT_EQUAL_UINT32( 255, b );
    TEST_ASSERT_EQUAL_INT( 0, rval );
}

void test_hsv2rgb_2(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    int rval = hsv2rgb(180, 100, 100, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 0, r );
    TEST_ASSERT_EQUAL_UINT32( 255, g );
    TEST_ASSERT_EQUAL_UINT32( 255, b );
    TEST_ASSERT_EQUAL_INT( 0, rval );
}

void test_hsv2rgb_3(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    int rval = hsv2rgb(120, 100, 50, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 0, r );
    TEST_ASSERT_EQUAL_UINT32( 127, g );
    TEST_ASSERT_EQUAL_UINT32( 0, b );
    TEST_ASSERT_EQUAL_INT( 0, rval );
}

void test_hsv2rgb_4(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    int rval =  hsv2rgb(67, 0, 75, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 191, r );
    TEST_ASSERT_EQUAL_UINT32( 191, g );
    TEST_ASSERT_EQUAL_UINT32( 191, b );
    TEST_ASSERT_EQUAL_INT( 0, rval );
}

void test_hsv2rgb_5(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    int rval = hsv2rgb(42, 96, 90, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 229, r );
    TEST_ASSERT_EQUAL_UINT32( 163, g );
    TEST_ASSERT_EQUAL_UINT32( 9, b );
    TEST_ASSERT_EQUAL_INT( 0, rval );
}

void test_hsv2rgb_6(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    int rval = hsv2rgb(300, 23, 64, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 163, r );
    TEST_ASSERT_EQUAL_UINT32( 125, g );
    TEST_ASSERT_EQUAL_UINT32( 163, b );
    TEST_ASSERT_EQUAL_INT( 0, rval );
}

void test_hsv2rgb_7(void)
{

    uint32_t g;
    uint32_t b;

    int rval = hsv2rgb(300, 23, 64, (uint32_t *)0, &g, &b);
    
    TEST_ASSERT_EQUAL_INT( -1, rval );
}

void test_hsv2rgb_8(void)
{

    uint32_t r;
    uint32_t b;

    int rval = hsv2rgb(300, 23, 64, &r, (uint32_t *)0, &b);
    
    TEST_ASSERT_EQUAL_INT( -1, rval );
}

void test_hsv2rgb_9(void)
{

    uint32_t r;
    uint32_t g;

    int rval = hsv2rgb(300, 23, 64, &r, &g, (uint32_t *)0);
    
    TEST_ASSERT_EQUAL_INT( -1, rval );
}

/*
    ##################################################
    ## Test PID
    ##################################################
*/

// #define MEANING_OF_LIFE 42
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

    TEST_ASSERT_EQUAL(88, decay_val);
    TEST_ASSERT_EQUAL(38, xTaskGetTickCount_fake.call_count);   
    TEST_ASSERT_EQUAL(32, pdMS_TO_TICKS_fake.call_count);  
}

void test_decay_pos_1(void)
{
    xTaskGetTickCount_fake.custom_fake = update_tick;
    pdMS_TO_TICKS_fake.custom_fake = tick_to_ms;
    
    uint32_t decay_val = 0;
    decay_val = decay_unit(decay_val, 20, 8, 8); 

    TEST_ASSERT_EQUAL(0, decay_val);
    TEST_ASSERT_EQUAL(0, xTaskGetTickCount_fake.call_count);   
    TEST_ASSERT_EQUAL(0, pdMS_TO_TICKS_fake.call_count);  
}

#endif // TEST
