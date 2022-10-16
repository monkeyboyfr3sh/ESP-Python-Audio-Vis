#ifdef TEST

#include "unity.h"

// DUT
#include "TCP_thread.h"
#include "TCP_thread.c" // Not sure if I should do this, but technically removes implicit warnings

// CMock lib 
#include "mock_esp_system.h"
#include "mock_TCP_test.h"

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
    ## Test setup_socket for TCP thread
    ##################################################
*/

void test_setup_socket_0(void)
{
    tcp_task_err_t result;

    // Test input params
    socket_information_t my_sock = {
        .socket_ID = 0,
    };
    int addr_family = 0;

    // Expected mock functions to be called
    init_sockaddr_storage_ExpectAndReturn(&my_sock, tcp_task_fail);

    result = setup_socket(&my_sock,addr_family);
    
    TEST_ASSERT_EQUAL_INT( (int)tcp_task_fail, (int)result );
}

void test_setup_socket_1(void)
{
    tcp_task_err_t result;

    // Test input params
    socket_information_t my_sock = {
        .socket_ID = 0,
    };
    int addr_family = 0;

    // Expected mock functions to be called
    init_sockaddr_storage_ExpectAndReturn(&my_sock, tcp_task_ok);
    create_bind_socket_ExpectAndReturn(&my_sock, tcp_task_ok);

    result = setup_socket(&my_sock,addr_family);
    
    TEST_ASSERT_EQUAL_INT( (int)tcp_task_ok, (int)result );
}

void test_setup_socket_2(void)
{
    tcp_task_err_t result;

    // Test input params
    socket_information_t my_sock = {
        .socket_ID = 0,
    };
    int addr_family = 0;

    // Expected mock functions to be called
    init_sockaddr_storage_ExpectAndReturn(&my_sock, tcp_task_ok);
    create_bind_socket_ExpectAndReturn(&my_sock, tcp_task_fail);

    result = setup_socket(&my_sock,addr_family);
    
    TEST_ASSERT_EQUAL_INT( (int)tcp_task_fail, (int)result );
}

/*
    ##################################################
    ## Test TCP server thread
    ##################################################
*/

void test_tcp_server_task_0(void)
{
    // Test input params
    char *arg = malloc(sizeof(char));
    arg[0] = 1;

    // Expected mock functions to be called
    init_sockaddr_storage_IgnoreAndReturn(tcp_task_ok);
    create_bind_socket_IgnoreAndReturn(tcp_task_fail);
    shutdown_socket_IgnoreAndReturn(tcp_task_fail);
    vTaskDelete_Ignore();

    tcp_server_task(arg);
}

void test_tcp_server_task_1(void)
{
    // Test input params
    char *arg = malloc(sizeof(char));
    arg[0] = 1;

    // Expected mock functions to be called
    init_sockaddr_storage_IgnoreAndReturn(tcp_task_ok);
    create_bind_socket_IgnoreAndReturn(tcp_task_ok);
    manage_socket_IgnoreAndReturn(tcp_task_ok);
    shutdown_socket_IgnoreAndReturn(tcp_task_fail);
    vTaskDelete_Ignore();

    tcp_server_task(arg);
}

void test_tcp_server_task_2(void)
{
    // Test input params
    char *arg = malloc(sizeof(char));
    arg[0] = 1;

    // Expected mock functions to be called
    init_sockaddr_storage_IgnoreAndReturn(tcp_task_ok);
    create_bind_socket_IgnoreAndReturn(tcp_task_ok);
    manage_socket_IgnoreAndReturn(tcp_task_fail);
    shutdown_socket_IgnoreAndReturn(tcp_task_fail);
    vTaskDelete_Ignore();

    tcp_server_task(arg);
}

#endif // TEST
