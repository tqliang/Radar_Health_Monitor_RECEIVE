/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#ifndef RESPIRATION_H
#define RESPIRATION_H

#include <stdint.h>

/* Public function declarations */
uint8_t get_respiration_rate(void);
void update_respiration_rate(void);

#endif // RESPIRATION_H