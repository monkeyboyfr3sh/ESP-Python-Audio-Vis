#include "../main/src/TCP_thread.c"
#include "build/test/mocks/mock_TCP_test.h"
#include "build/test/mocks/mock_esp_system.h"
#include "../main/inc/TCP_thread.h"
#include "C:/Ruby25/lib/ruby/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"














int test_count = 0;

void setUp(void)

{

    test_count++;

}

void tearDown(void)

{

}















void test_setup_socket_0(void)

{

    tcp_task_err_t result;





    socket_information_t my_sock = {

        .socket_ID = 0,

    };

    int addr_family = 0;





    init_sockaddr_storage_CMockExpectAndReturn(39, &my_sock, tcp_task_fail);



    result = setup_socket(&my_sock,addr_family);



    UnityAssertEqualNumber((UNITY_INT)(((int)tcp_task_fail)), (UNITY_INT)(((int)result)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

}



void test_setup_socket_1(void)

{

    tcp_task_err_t result;





    socket_information_t my_sock = {

        .socket_ID = 0,

    };

    int addr_family = 0;





    init_sockaddr_storage_CMockExpectAndReturn(57, &my_sock, tcp_task_ok);

    create_bind_socket_CMockExpectAndReturn(58, &my_sock, tcp_task_ok);



    result = setup_socket(&my_sock,addr_family);



    UnityAssertEqualNumber((UNITY_INT)(((int)tcp_task_ok)), (UNITY_INT)(((int)result)), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

}



void test_setup_socket_2(void)

{

    tcp_task_err_t result;





    socket_information_t my_sock = {

        .socket_ID = 0,

    };

    int addr_family = 0;





    init_sockaddr_storage_CMockExpectAndReturn(76, &my_sock, tcp_task_ok);

    create_bind_socket_CMockExpectAndReturn(77, &my_sock, tcp_task_fail);



    result = setup_socket(&my_sock,addr_family);



    UnityAssertEqualNumber((UNITY_INT)(((int)tcp_task_fail)), (UNITY_INT)(((int)result)), (

   ((void *)0)

   ), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_INT);

}















void test_tcp_server_task_0(void)

{



    char *arg = malloc(sizeof(char));

    arg[0] = 1;





    init_sockaddr_storage_CMockIgnoreAndReturn(97, tcp_task_ok);

    create_bind_socket_CMockIgnoreAndReturn(98, tcp_task_fail);

    shutdown_socket_CMockIgnoreAndReturn(99, tcp_task_fail);

    vTaskDelete_CMockIgnore();



    tcp_server_task(arg);

}



void test_tcp_server_task_1(void)

{



    char *arg = malloc(sizeof(char));

    arg[0] = 1;





    init_sockaddr_storage_CMockIgnoreAndReturn(112, tcp_task_ok);

    create_bind_socket_CMockIgnoreAndReturn(113, tcp_task_ok);

    manage_socket_CMockIgnoreAndReturn(114, tcp_task_ok);

    shutdown_socket_CMockIgnoreAndReturn(115, tcp_task_fail);

    vTaskDelete_CMockIgnore();



    tcp_server_task(arg);

}



void test_tcp_server_task_2(void)

{



    char *arg = malloc(sizeof(char));

    arg[0] = 1;





    init_sockaddr_storage_CMockIgnoreAndReturn(128, tcp_task_ok);

    create_bind_socket_CMockIgnoreAndReturn(129, tcp_task_ok);

    manage_socket_CMockIgnoreAndReturn(130, tcp_task_fail);

    shutdown_socket_CMockIgnoreAndReturn(131, tcp_task_fail);

    vTaskDelete_CMockIgnore();



    tcp_server_task(arg);

}
