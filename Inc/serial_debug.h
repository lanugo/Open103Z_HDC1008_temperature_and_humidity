/*
 * This module is used for debugging messages and values to the serial console.
 *
 * Copyright (c) 2015 Tino Ernst
 *
 * This file is released under the GPLv2.
 */

#ifndef _SERIAL_DEBUG_H
#define _SERIAL_DEBUG_H

#include "stm32f1xx_hal.h"

// debug USART used for serial console
#define DEBUG_USART		huart1

extern UART_HandleTypeDef DEBUG_USART;

// macros for debug messages
#define		_DBC(x)		debug_char(&DEBUG_USART, x);
#define		_DBG(x)		debug_string(&DEBUG_USART, x);
#define		_DBF(x)		debug_float(&DEBUG_USART, x);

void debug_char(UART_HandleTypeDef *huart, uint8_t c);
void debug_string(UART_HandleTypeDef *huart, char *str);
void debug_float(UART_HandleTypeDef *huart, float f);

#endif
