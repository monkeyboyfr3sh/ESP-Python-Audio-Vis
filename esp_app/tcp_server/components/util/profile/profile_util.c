#include "utils.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "perfmon.h"

static const char* TAG = "util-profiler";

// Table with dedicated performance counters
static uint32_t pm_check_table[] = {
    XTPERF_CNT_CYCLES, XTPERF_MASK_CYCLES, // Total cycles
    XTPERF_CNT_D_STALL, XTPERF_MASK_D_STALL_CACHE_MISS, // data related cache miss stall
    XTPERF_CNT_I_STALL, XTPERF_MASK_I_STALL_CACHE_MISS, // instruction related cache miss stall
};

#define TOTAL_CALL_AMOUNT 10
#define PERFMON_TRACELEVEL -1 // -1 - will ignore trace level

void profile_utils(void *params)
{
    ESP_LOGI(TAG, "###########################################");
    ESP_LOGI(TAG, "Starting profling of utils functions");

    xtensa_perfmon_config_t pm_config = {};

    ESP_LOGI(TAG, "Start test of hsv2rgb");
    pm_config.counters_size = sizeof(pm_check_table) / sizeof(uint32_t) / 2;
    pm_config.select_mask = pm_check_table;
    pm_config.repeat_count = TOTAL_CALL_AMOUNT;
    pm_config.max_deviation = 1;
    pm_config.call_function = hsv2rgb;
    pm_config.callback = xtensa_perfmon_view_cb;
    pm_config.callback_params = stdout;
    pm_config.tracelevel = PERFMON_TRACELEVEL;

    xtensa_perfmon_exec(&pm_config);

    ESP_LOGI(TAG, "Start test of pid_loop_step");
    pm_config.counters_size = sizeof(pm_check_table) / sizeof(uint32_t) / 2;
    pm_config.select_mask = pm_check_table;
    pm_config.repeat_count = TOTAL_CALL_AMOUNT;
    pm_config.max_deviation = 1;
    pm_config.call_function = pid_loop_step;
    pm_config.callback = xtensa_perfmon_view_cb;
    pm_config.callback_params = stdout;
    pm_config.tracelevel = PERFMON_TRACELEVEL;

    xtensa_perfmon_exec(&pm_config);

    ESP_LOGI(TAG, "Start test of decay_pos");
    pm_config.counters_size = sizeof(pm_check_table) / sizeof(uint32_t) / 2;
    pm_config.select_mask = pm_check_table;
    pm_config.repeat_count = TOTAL_CALL_AMOUNT;
    pm_config.max_deviation = 1;
    pm_config.call_function = decay_pos;
    pm_config.callback = xtensa_perfmon_view_cb;
    pm_config.callback_params = stdout;
    pm_config.tracelevel = PERFMON_TRACELEVEL;

    xtensa_perfmon_exec(&pm_config);

    ESP_LOGI(TAG, "End profiling of utils functions");
    ESP_LOGI(TAG, "###########################################\n");

    vTaskDelete(NULL);
}