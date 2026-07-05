/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#ifndef UART_H
#define UART_H

/* UART1 引脚定义 */
#define UART1_TX_GPIO 17
#define UART1_RX_GPIO 18

/* Public function declarations */
void uart1_init(void);

#endif // UART_H