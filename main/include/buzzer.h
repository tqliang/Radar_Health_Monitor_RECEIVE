#ifndef BUZZER_H
#define BUZZER_H

/* 蜂鸣器 GPIO 引脚 */
#define BUZZER_GPIO 37

/* Public function declarations */
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);

#endif /* BUZZER_H */