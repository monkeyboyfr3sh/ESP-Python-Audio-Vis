#include "../main/inc/utils.h"
#include "C:/Ruby25/lib/ruby/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








int test_count = 0;

void setUp(void)

{

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



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(31)));

}



void test_pid_1(void)

{

    float result;



    float prev_pos = 0.0;

    float new_pos = -1.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(43)));

}



void test_pid_2(void)

{

    float result;



    float prev_pos = -1.0;

    float new_pos = 0.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(55)));

}



void test_pid_3(void)

{

    float result;



    float prev_pos = -1.0;

    float new_pos = -1.0;



    result = pid_loop_step(prev_pos, new_pos, 1.0, 0.0, 0.0);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((-1.0)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((-1.0))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(67)));

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

        UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((new_pos)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((new_pos))), (UNITY_FLOAT)((UNITY_FLOAT)((result))), ((

       ((void *)0)

       )), (UNITY_UINT)((UNITY_UINT)(83)));

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

   ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(105), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_1(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(240, 100, 100, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(118), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((255)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_2(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(180, 100, 100, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((255)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((255)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(135), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_3(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(120, 100, 50, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((127)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_4(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(67, 0, 75, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((191)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(163), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((191)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(164), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((191)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(166), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_5(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(42, 96, 90, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((229)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(178), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((163)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(179), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((9)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(180), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_6(void)

{



    uint32_t r;

    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(300, 23, 64, &r, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((163)), (UNITY_INT)(UNITY_UINT32)((r)), (

   ((void *)0)

   ), (UNITY_UINT)(193), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((125)), (UNITY_INT)(UNITY_UINT32)((g)), (

   ((void *)0)

   ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((163)), (UNITY_INT)(UNITY_UINT32)((b)), (

   ((void *)0)

   ), (UNITY_UINT)(195), UNITY_DISPLAY_STYLE_UINT32);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_7(void)

{



    uint32_t g;

    uint32_t b;



    int rval = hsv2rgb(300, 23, 64, (uint32_t *)0, &g, &b);



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(207), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_8(void)

{



    uint32_t r;

    uint32_t b;



    int rval = hsv2rgb(300, 23, 64, &r, (uint32_t *)0, &b);



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(218), UNITY_DISPLAY_STYLE_INT);

}



void test_hsv2rgb_9(void)

{



    uint32_t r;

    uint32_t g;



    int rval = hsv2rgb(300, 23, 64, &r, &g, (uint32_t *)0);



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((rval)), (

   ((void *)0)

   ), (UNITY_UINT)(229), UNITY_DISPLAY_STYLE_INT);

}
