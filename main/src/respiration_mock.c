#include "respiration.h"
#include "radar_receiver.h"
#include "esp_log.h"

static const char *RESP_TAG = "respiration";

/* 默认静息呼吸频率 15 次/分钟 */
static uint8_t respiration_rate = 15;

uint8_t get_respiration_rate(void)
{
    return respiration_rate;
}

void update_respiration_rate(void)
{
    if (radar_data_available())
    {
        float raw = radar_get_breath_bpm();
        if (raw > 0.0f)
        {
            respiration_rate = (uint8_t)(raw + 0.5f);
            ESP_LOGI(RESP_TAG, "Radar breath rate: %.1f -> %u bpm", (double)raw, respiration_rate);
        }
    }
}