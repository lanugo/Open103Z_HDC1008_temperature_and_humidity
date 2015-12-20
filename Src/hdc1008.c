/*
 * Driver for the HDC1008 temperature and humidity sensor
 * for usage with STM32 microcontroller and the HAL.
 *
 * Copyright (c) 2015 Tino Ernst
 *
 * This file is released under the GPLv2.
 */

#include "hdc1008.h"

#define I2C_WAIT_TIMEOUT	300

static int hdc_read_register16(struct hdc1008_ctx *ctx, uint8_t reg, uint16_t *val, uint32_t delay)
{
	uint8_t data[2];

	if (HAL_I2C_Master_Transmit(ctx->hi2c, (ctx->address << 1), &reg, 1, I2C_WAIT_TIMEOUT) != HAL_OK)
		 return 0;

	HAL_Delay(delay);

	if (HAL_I2C_Master_Receive(ctx->hi2c, (ctx->address << 1), data, 2, I2C_WAIT_TIMEOUT) != HAL_OK)
		 return 0;

	*val = (data[0] << 8) | data[1];
	return 1;
}

static int hdc_read_register32(struct hdc1008_ctx *ctx, uint8_t reg, uint32_t *val, uint32_t delay)
{
	uint8_t data[4];

	if (HAL_I2C_Master_Transmit(ctx->hi2c, (ctx->address << 1), &reg, 1, I2C_WAIT_TIMEOUT) != HAL_OK)
		 return 0;

	HAL_Delay(delay);

	if (HAL_I2C_Master_Receive(ctx->hi2c, (ctx->address << 1), data, 4, I2C_WAIT_TIMEOUT) != HAL_OK)
		 return 0;

	*val = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	return 1;
}

/*********************************************************************//**
 * @brief		Initialize one HDC1008 at the specified I2C port.
 * @param[in]	ctx		HDC context, where I2C port and device address is set
 * @return		1 if an HDC device was found on the bus, 0 otherwise
 **********************************************************************/
int hdc1008_init(struct hdc1008_ctx *ctx)
{
	uint16_t val;

	if (!hdc_read_register16(ctx, HDC1008_MANUFACTURER_ID_REG, &val, 0))
		return 0;
	if (val != 0x5449)
		return 0;

	if (!hdc_read_register16(ctx, HDC1008_DEVICE_ID_REG, &val, 0))
		return 0;
	if (val != 0x1000)
		return 0;

	return 1;
}

int hdc1008_read_temperature_and_humidity(struct hdc1008_ctx *ctx, float *temp, float *hum)
{
	uint32_t i;

	/*
	 * Start measurement, wait until the sensor did the measurement with its ADC
	 * and then read the 16-bit temperature + 16-bit humidity.
	 */
	if (!hdc_read_register32(ctx, HDC1008_TEMPERATURE_REG, &i, 50))
		return 0;

	*temp = ((float)(i >> 16)) / 65536 * 165 - 40;
	*hum = ((float)(i & 0xFFFF)) / 65536 * 100;

	return 1;
}
