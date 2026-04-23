/*
 * tac5112.c
 *
 *  Created on: Oct 4, 2025
 *      Author: emilm
 */

#include "tac5112.h"
#include "stdio.h"

void ledStatus(HAL_StatusTypeDef status_i2c)
{
	if (status_i2c == HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOB, LEDB_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, LEDB_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC, LEDR_Pin, GPIO_PIN_RESET);
		while (1);
	}
}

uint8_t TAC5112_init()
{
	HAL_StatusTypeDef status_i2c = 0;
	uint8_t i2c_data;
	HAL_Delay(50);

	i2c_data = 0x00;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_PAGE_CFG_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Set page 0, 0000000
	ledStatus(status_i2c);

	i2c_data = 0x01;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_SW_RESET_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Software reset, 0000000 1
	ledStatus(status_i2c);

	i2c_data = 0x09;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_DEV_MISC_CFG_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Device configuration, bits 0 and 3, 00 00 1 0 0 1
	ledStatus(status_i2c);

	i2c_data = 0x80;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_INTF_CFG2_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Primary ASI configuration, 1 000 000 0
	ledStatus(status_i2c);

	i2c_data = 0x00;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_ASI_CFG1_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Asi configuration 00 00 0 0 0 0
	ledStatus(status_i2c);

	i2c_data = 0x40;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_PASI_CFG0_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // 16 bit, I2S mode, 01 00 0 0 0 0
	ledStatus(status_i2c);

	i2c_data = 0x20;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_PASI_RX_CH1_CFG_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Primary ASI channel1 configuration, 00 1 00000
	ledStatus(status_i2c);

	i2c_data = 0x30;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_PASI_RX_CH2_CFG_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Primary ASI channel2 configuration, 00 1 10000
	ledStatus(status_i2c);



	i2c_data = 0x36;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_OUT1x_CFG0_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // DAC input, pseudo-diff-external sense, AVDD by 2, 001 101 1 0
	ledStatus(status_i2c);

	i2c_data = 0x60;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_OUT1x_CFG1_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Right channel, output drive, level control, bandwidth, 01 100 0 0 0
	ledStatus(status_i2c);

	i2c_data = 0x60;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_OUT1x_CFG2_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Right Vcom, output drive, level control, input coupling, 01 100 0 0 0
	ledStatus(status_i2c);

	i2c_data = 0x32;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_OUT2x_CFG0_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // DAC input, pseudo-diff???, AVDD by 2(?), 001 100 1 0
	ledStatus(status_i2c);

	i2c_data = 0x60;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_OUT2x_CFG1_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Left channel, output drive, level control, bandwidth, 01 100 0 0 0
	ledStatus(status_i2c);

	i2c_data = 0x60;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_OUT2x_CFG2_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Left sense, output drive, level control, input coupling, 01 100 0 0 0
	ledStatus(status_i2c);



	i2c_data = 0x0C;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_CH_EN_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Enable CH1,CH2 output 0 0 0 0 1 1 0 0
	ledStatus(status_i2c);

	i2c_data = 0x40;
	status_i2c = HAL_I2C_Mem_Write(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_PWR_CFG_REG, I2C_MEMADD_SIZE_8BIT, &i2c_data, 1, 100); // Power enabled DAC channels 0 1 0 0 0 0 0 0
	ledStatus(status_i2c);

	HAL_Delay(10);
	return 0;
}

int TAC5112_play(int16_t *pbuffer, uint32_t size)
{
	HAL_I2S_Transmit_DMA(&TAC5112_I2S, (uint16_t * )pbuffer, size);
	return 0;
}
HAL_StatusTypeDef TAC5112_Read_Sts(uint8_t *sts0, uint8_t *sts1, uint8_t *clk_sts0, uint8_t *clk_sts2, uint8_t *err_sts0, uint8_t *err_sts1)
{
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Read(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_DEV_STS0_REG, I2C_MEMADD_SIZE_8BIT, sts0, 1, 100); // Read channel power status
		if (status != HAL_OK)
			return status;
	status = HAL_I2C_Mem_Read(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_DEV_STS1_REG, I2C_MEMADD_SIZE_8BIT, sts1, 1, 100); // Read device mode status
		if (status != HAL_OK)
			return status;
	status = HAL_I2C_Mem_Read(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_CLK_DET_STS0, I2C_MEMADD_SIZE_8BIT, clk_sts0, 1, 100); // Read primary asi clk status
		if (status != HAL_OK)
			return status;
	status = HAL_I2C_Mem_Read(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_CLK_DET_STS2, I2C_MEMADD_SIZE_8BIT, clk_sts2, 2, 100); // MSB bits prim FSYNC to src ratio
		if (status != HAL_OK)
			return status;
	status = HAL_I2C_Mem_Read(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_CLK_ERR_STS0, I2C_MEMADD_SIZE_8BIT, err_sts0, 1, 100); // Clk error sts 0
		if (status != HAL_OK)
			return status;
	status = HAL_I2C_Mem_Read(&TAC5112_I2C, TAC5112_I2C_ADDRESS, TAC5112_CLK_ERR_STS1, I2C_MEMADD_SIZE_8BIT, err_sts1, 1, 100); // Clk error sts 0
		if (status != HAL_OK)
			return status;


	return HAL_OK;
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	if (hi2s == &TAC5112_I2S)
	{
		AUDIO_I2S_TxCpltCallback();
	}
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	if (hi2s == &TAC5112_I2S)
	{
		AUDIO_I2S_TxHalfCpltCallback();
	}
}
__weak void AUDIO_I2S_TxCpltCallback(void)
{

}
__weak void AUDIO_I2S_TxHalfCpltCallback(void)
{

}





























