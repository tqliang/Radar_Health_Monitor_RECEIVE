/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#ifndef KEY_H
#define KEY_H

#include <stdint.h>

/* 按键数量 */
#define KEY_NUM 4

/* 按键索引定义 */
#define KEY1 0
#define KEY2 1
#define KEY3 2
#define KEY4 3

/* Public function declarations */
void key_init(void);
uint8_t key_read(uint8_t key_num);
uint8_t key_is_pressed(uint8_t key_num);

#endif // KEY_H