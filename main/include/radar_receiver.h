/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#ifndef RADAR_RECEIVER_H
#define RADAR_RECEIVER_H

#include <stdint.h>
#include <stdbool.h>

/* 雷达帧协议常量 */
#define RADAR_FRAME_SIZE        16      /* 帧总长度: 2(头) + 1(标志) + 4(cnt) + 4(呼吸) + 4(心率) + 1(CRC) */
#define RADAR_FRAME_HEADER_0    0xAA
#define RADAR_FRAME_HEADER_1    0x55
#define RADAR_FRAME_FLAG        0x01

/* 均值滤波窗口大小 */
#define RADAR_FILTER_WINDOW     5

/* Public function declarations */
void radar_receiver_init(void);
bool radar_data_available(void);
float radar_get_breath_bpm(void);
float radar_get_heart_bpm(void);

#endif /* RADAR_RECEIVER_H */