#include "LED_thread.h"

#include "perfmon.h"

static const char* TAG = "example";

#define TOTAL_CALL_AMOUNT 1
#define PERFMON_TRACELEVEL -1 // -1 - will ignore trace level

// Table with dedicated performance counters
static uint32_t pm_check_table[] = {
    XTPERF_CNT_CYCLES, XTPERF_MASK_CYCLES, // Total cycles
    // XTPERF_CNT_INSN, XTPERF_MASK_COMMITTED_INSN, // Total instructions
    // XTPERF_CNT_D_LOAD_U1, XTPERF_MASK_D_LOAD_LOCAL_MEM, // Mem read
    // XTPERF_CNT_D_STORE_U1, XTPERF_MASK_D_STORE_LOCAL_MEM, // Mem write
    // XTPERF_CNT_OVERFLOW, XTPERF_MASK_OVERFLOW, // Last test cycle
};

void profile_led_thread(void *params)
{
    xtensa_perfmon_config_t pm_config = {};

    int num_led = 10;

    ESP_LOGI(TAG, "Start test with user defined statistic");
    pm_config.counters_size = sizeof(pm_check_table) / sizeof(uint32_t) / 2;
    pm_config.select_mask = pm_check_table;
    pm_config.repeat_count = TOTAL_CALL_AMOUNT;
    pm_config.max_deviation = 1;
    pm_config.call_function = update_num_led;
    pm_config.callback = xtensa_perfmon_view_cb;
    pm_config.callback_params = (void *)num_led;
    pm_config.tracelevel = PERFMON_TRACELEVEL;

    xtensa_perfmon_exec(&pm_config);

    ESP_LOGI(TAG, "The End");
}