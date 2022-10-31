#include "LED_thread.h"

#include "perfmon.h"

static const char* TAG = "led_thread-profiler";

#define TOTAL_CALL_AMOUNT 100
#define PERFMON_TRACELEVEL -1 // -1 - will ignore trace level

// Table with dedicated performance counters
static uint32_t pm_check_table[] = {
    XTPERF_CNT_CYCLES, XTPERF_MASK_CYCLES, // Total cycles
    XTPERF_CNT_D_STALL, XTPERF_MASK_D_STALL_CACHE_MISS, // data related cache miss stall
    XTPERF_CNT_I_STALL, XTPERF_MASK_I_STALL_CACHE_MISS, // instruction related cache miss stall
};

void init_deinit_strip(void *params)
{
    const int num_led = 20;

    // Init the strip
    led_strip_t* strip = update_num_led(num_led);
    // Deinit the strip
    deinit_led_strip(strip);
}


void profile_led_thread(void *params)
{
    ESP_LOGI(TAG, "###########################################");
    ESP_LOGI(TAG, "Starting profling of LED_thread functions");

    xtensa_perfmon_config_t pm_config = {};

    int num_led = 10;

    ESP_LOGI(TAG, "Start test of init_deinit_strip");
    pm_config.counters_size = sizeof(pm_check_table) / sizeof(uint32_t) / 2;
    pm_config.select_mask = pm_check_table;
    // pm_config.counters_size = sizeof(xtensa_perfmon_select_mask_all) / sizeof(uint32_t) / 2;
    // pm_config.select_mask = xtensa_perfmon_select_mask_all;
    pm_config.repeat_count = TOTAL_CALL_AMOUNT;
    pm_config.max_deviation = 1;
    pm_config.call_function = init_deinit_strip;
    pm_config.callback = xtensa_perfmon_view_cb;
    pm_config.callback_params = stdout;
    pm_config.tracelevel = PERFMON_TRACELEVEL;

    esp_log_level_set("led",ESP_LOG_NONE);
    xtensa_perfmon_exec(&pm_config);

    ESP_LOGI(TAG, "End profling of LED_thread functions");
    ESP_LOGI(TAG, "###########################################\n");
}