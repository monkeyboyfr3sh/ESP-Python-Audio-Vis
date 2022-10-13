#ifdef TEST

#include "unity.h"

#include "utils.h"

int test_count = 0;
void setUp(void)
{
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

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
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

    hsv2rgb(0, 100, 100, &r, &g, &b);

    TEST_ASSERT_EQUAL_UINT32( 255, r );
    TEST_ASSERT_EQUAL_UINT32( 0, g );
    TEST_ASSERT_EQUAL_UINT32( 0, b );
}

void test_hsv2rgb_1(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    hsv2rgb(240, 100, 100, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 0, r );
    TEST_ASSERT_EQUAL_UINT32( 0, g );
    TEST_ASSERT_EQUAL_UINT32( 255, b );
}

void test_hsv2rgb_2(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    hsv2rgb(180, 100, 100, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 0, r );
    TEST_ASSERT_EQUAL_UINT32( 255, g );
    TEST_ASSERT_EQUAL_UINT32( 255, b );
}

void test_hsv2rgb_3(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    hsv2rgb(120, 100, 50, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 0, r );
    TEST_ASSERT_EQUAL_UINT32( 127, g );
    TEST_ASSERT_EQUAL_UINT32( 0, b );
}

void test_hsv2rgb_4(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    hsv2rgb(67, 0, 75, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 191, r );
    TEST_ASSERT_EQUAL_UINT32( 191, g );
    TEST_ASSERT_EQUAL_UINT32( 191, b );
}

void test_hsv2rgb_5(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    hsv2rgb(42, 96, 90, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 229, r );
    TEST_ASSERT_EQUAL_UINT32( 163, g );
    TEST_ASSERT_EQUAL_UINT32( 9, b );
}

void test_hsv2rgb_6(void)
{

    uint32_t r;
    uint32_t g;
    uint32_t b;

    hsv2rgb(300, 23, 64, &r, &g, &b);
    
    TEST_ASSERT_EQUAL_UINT32( 163, r );
    TEST_ASSERT_EQUAL_UINT32( 125, g );
    TEST_ASSERT_EQUAL_UINT32( 163, b );
}

#endif // TEST
