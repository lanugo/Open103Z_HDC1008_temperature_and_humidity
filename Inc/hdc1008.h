/*
 * Driver for the HDC1008 temperature and humidity sensor
 * for usage with STM32 microcontroller and the HAL.
 *
 * Copyright (c) 2015 Tino Ernst
 *
 * This file is released under the GPLv2.
 */

#ifndef _HDC1008_H
#define _HDC1008_H

#include <inttypes.h>
#include "stm32f1xx_hal.h"

#define HDC1008_TEMPERATURE_REG			0x00
#define HDC1008_MANUFACTURER_ID_REG		0xFE
#define HDC1008_DEVICE_ID_REG			0xFF

struct hdc1008_ctx {
	I2C_HandleTypeDef *hi2c;
	uint8_t address;
};

int hdc1008_init(struct hdc1008_ctx *ctx);
int hdc1008_read_temperature_and_humidity(struct hdc1008_ctx *ctx, float *temp, float *hum);

#endif
