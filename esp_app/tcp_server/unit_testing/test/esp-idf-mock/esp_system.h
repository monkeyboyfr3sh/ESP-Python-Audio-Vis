#ifndef _MOCK_TEST_FUNC_H_
#define _MOCK_TEST_FUNC_H_

// I've hijacked esp_system to mock common function calls for esp idf
void vTaskDelay(int i);
int xTaskGetTickCount( void );
int pdMS_TO_TICKS (int ms);

#endif