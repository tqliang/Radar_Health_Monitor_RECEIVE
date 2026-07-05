#ifndef ALARM_H
#define ALARM_H

#include <stdbool.h>
#include <stdint.h>

/* 报警阈值定义 (可自定义修改) */
#define ALARM_HEART_RATE_MIN     40    /* 心率过低阈值 (bpm) */
#define ALARM_HEART_RATE_MAX     120   /* 心率过高阈值 (bpm) */
#define ALARM_RESPIRATION_MIN    8     /* 呼吸频率过低阈值 (次/分钟) */
#define ALARM_RESPIRATION_MAX    30    /* 呼吸频率过高阈值 (次/分钟) */

/* 报警检测任务周期 (ms) */
#define ALARM_CHECK_PERIOD_MS    500

/* Public function declarations */
void alarm_init(void);
bool alarm_is_enabled(void);
void alarm_task(void *param);

#endif /* ALARM_H */