#include "alarm.h"
#include "buzzer.h"
#include "key.h"
#include "heart_rate.h"
#include "respiration.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *ALARM_TAG = "alarm";

static bool alarm_enabled = false;
static bool buzzer_active = false;

void alarm_init(void)
{
    ESP_LOGI(ALARM_TAG, "Alarm module initialized");
    ESP_LOGI(ALARM_TAG, "Heart rate thresholds: %d - %d bpm", ALARM_HEART_RATE_MIN, ALARM_HEART_RATE_MAX);
    ESP_LOGI(ALARM_TAG, "Respiration thresholds: %d - %d bpm", ALARM_RESPIRATION_MIN, ALARM_RESPIRATION_MAX);
}

bool alarm_is_enabled(void)
{
    return alarm_enabled;
}

static bool is_heart_rate_abnormal(uint8_t hr)
{
    return (hr < ALARM_HEART_RATE_MIN || hr > ALARM_HEART_RATE_MAX);
}

static bool is_respiration_abnormal(uint8_t rr)
{
    return (rr < ALARM_RESPIRATION_MIN || rr > ALARM_RESPIRATION_MAX);
}

void alarm_task(void *param)
{
    (void)param;
    ESP_LOGI(ALARM_TAG, "Alarm monitor task started");

    bool last_key2_state = false;

    while (1)
    {
        bool key2_pressed = key_is_pressed(KEY2);

        if (key2_pressed && !last_key2_state)
        {
            alarm_enabled = !alarm_enabled;
            if (alarm_enabled)
            {
                ESP_LOGI(ALARM_TAG, "Alarm ENABLED");
            }
            else
            {
                ESP_LOGI(ALARM_TAG, "Alarm DISABLED");
                buzzer_off();
                buzzer_active = false;
            }
        }
        last_key2_state = key2_pressed;

        if (alarm_enabled)
        {
            uint8_t hr = get_heart_rate();
            uint8_t rr = get_respiration_rate();

            bool hr_abnormal = is_heart_rate_abnormal(hr);
            bool rr_abnormal = is_respiration_abnormal(rr);

            if (hr_abnormal || rr_abnormal)
            {
                if (!buzzer_active)
                {
                    buzzer_on();
                    buzzer_active = true;
                    ESP_LOGW(ALARM_TAG, "Abnormal detected! HR=%d bpm, RR=%d bpm -> Buzzer ON", hr, rr);
                }
            }
            else
            {
                if (buzzer_active)
                {
                    buzzer_off();
                    buzzer_active = false;
                    ESP_LOGI(ALARM_TAG, "Vital signs normal -> Buzzer OFF");
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(ALARM_CHECK_PERIOD_MS));
    }
}