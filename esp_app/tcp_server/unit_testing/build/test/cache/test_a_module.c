#include "src/adc.h"
#include "src/utils.h"
#include "C:/Ruby25/lib/ruby/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








int test_count = 0;

void setUp(void)

{

    test_count++;

}

void tearDown(void)

{

}



void test_p_0(void)

{

    float result;



    float prev_pos = 0.0;

    float new_pos = 1.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(26)));

}





void test_p_1(void)

{

    float result;



    float prev_pos = 0.0;

    float new_pos = -1.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(39)));

}





void test_p_2(void)

{

    float result;



    float prev_pos = -1.0;

    float new_pos = 0.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(52)));

}





void test_p_3(void)

{

    float result;



    float prev_pos = -1.0;

    float new_pos = -1.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(65)));

}





void test_p_4(void)

{

    float result;



    float prev_pos = 0.0;

    float new_pos = 0.0;



    for(int i = 0;i<100;i++){



        prev_pos = new_pos;

        new_pos++;



        result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);

        UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((new_pos)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((new_pos))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

       ((void *)0)

       )), (UNITY_UINT)((UNITY_UINT)(82)));

    }



}
