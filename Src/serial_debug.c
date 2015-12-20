/*
 * This module is used for debugging messages and values to the serial console.
 *
 * Copyright (c) 2015 Tino Ernst
 *
 * This file is released under the GPLv2.
 */

#include "serial_debug.h"

void debug_char(UART_HandleTypeDef *huart, uint8_t c)
{
	HAL_UART_Transmit(huart, &c, 1, 300);
}

void debug_string(UART_HandleTypeDef *huart, char *str)
{
	uint8_t *s = (uint8_t*)str;

	while (*s)
		debug_char(huart, *s++);
}

void debug_float(UART_HandleTypeDef *huart, float f)
{
	uint8_t c;
	if (f < 0) {
		f *= -1;
		debug_char(huart, '-');
	}

	uint8_t c1=(int)f%10;
	uint8_t c2=((int)f/10)%10;
	uint8_t c3=((int)f/100)%10;
	uint8_t c4=((int)f/1000)%10;
	uint8_t c5=((int)f/10000)%10;
	uint8_t c6=((int)f/100000)%10;
	debug_char(huart, '0'+c6);
	debug_char(huart, '0'+c5);
	debug_char(huart, '0'+c4);
	debug_char(huart, '0'+c3);
	debug_char(huart, '0'+c2);
	debug_char(huart, '0'+c1);
	debug_char(huart, '.');
	c = ((int)(f*10))%10;
	debug_char(huart, '0'+c);
	c = ((int)(f*100))%10;
	debug_char(huart, '0'+c);
	c = ((int)(f*1000))%10;
	debug_char(huart, '0'+c);
}
