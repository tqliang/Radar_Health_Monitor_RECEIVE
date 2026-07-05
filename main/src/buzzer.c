#include "buzzer.h"
#include "driver/gpio.h"

void buzzer_init(void)
{
    gpio_reset_pin(BUZZER_GPIO);
    gpio_set_direction(BUZZER_GPIO, GPIO_MODE_OUTPUT);
    buzzer_off();
}

void buzzer_on(void)
{
    gpio_set_level(BUZZER_GPIO, 0);
}

void buzzer_off(void)
{
    gpio_set_level(BUZZER_GPIO, 1);
}