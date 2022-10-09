#ifdef TEST

#include "unity.h"

#include "utils.h"
#include "adc.h"

int test_count = 0;
void setUp(void)
{
    test_count++;
}
void tearDown(void)
{
}
//Test Case 0
void test_p_0(void)
{
    float result;
    
    float prev_pos = 0.0;
    float new_pos = 1.0;

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT( 1.0, result );
}

//Test Case 1
void test_p_1(void)
{
    float result;
    
    float prev_pos = 0.0;
    float new_pos = -1.0;

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT( -1.0, result );
}

//Test Case 2
void test_p_2(void)
{
    float result;
    
    float prev_pos = -1.0;
    float new_pos = 0.0;

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT( -1.0, result );
}

//Test Case 3
void test_p_3(void)
{
    float result;
    
    float prev_pos = -1.0;
    float new_pos = -1.0;

    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT( -1.0, result );
}

//Test Case 4
void test_p_4(void)
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

#endif // TEST
