/*
 * tac5112.h
 *
 *  Created on: Oct 4, 2025
 *      Author: emilm
 */

#include "main.h"

extern I2C_HandleTypeDef hi2c2;
extern I2S_HandleTypeDef hi2s2;

#define TAC5112_I2C hi2c2
#define TAC5112_I2S hi2s2

#define TAC5112_I2C_ADDRESS (0x50 << 1)

/*
 * Important Device Register Addresses
 */

#define TAC5112_PAGE_CFG_REG 0x00
#define TAC5112_SW_RESET_REG 0x01

#define TAC5112_DEV_MISC_CFG_REG 0x02
#define TAC5112_PASI_CFG0_REG 0x1A

#define TAC5112_INTF_CFG2_REG 0x11
#define TAC5112_ASI_CFG1_REG 0x19

#define TAC5112_CH_EN_REG 0x76

#define TAC5112_PASI_RX_CH1_CFG_REG 0x28
#define TAC5112_PASI_RX_CH2_CFG_REG 0x29


#define TAC5112_PWR_CFG_REG 0x78

/*
 * Status Device Register Addresses
 */

#define TAC5112_DEV_STS0_REG 0x79
#define TAC5112_DEV_STS1_REG 0x7A

#define TAC5112_CLK_DET_STS0 0x3E
#define TAC5112_CLK_DET_STS2 0x40
#define TAC5112_CLK_ERR_STS0 0x3C
#define TAC5112_CLK_ERR_STS1 0x3D

/*
 * Other Device Register Addresses
 */

#define TAC5112_OUT1x_CFG0_REG 0x64
#define TAC5112_OUT1x_CFG1_REG 0x65
#define TAC5112_OUT1x_CFG2_REG 0x66

#define TAC5112_OUT2x_CFG0_REG 0x6B
#define TAC5112_OUT2x_CFG1_REG 0x6C
#define TAC5112_OUT2x_CFG2_REG 0x6D


/*
 * End of Device Register Addresses
 */

uint8_t TAC5112_init();
int TAC5112_play(int16_t *pbuffer, uint32_t size);
HAL_StatusTypeDef TAC5112_Read_Sts(uint8_t *sts0, uint8_t *sts1, uint8_t *clk_sts0, uint8_t *clk_sts2, uint8_t *err_sts0, uint8_t *err_sts1);

void AUDIO_I2S_TxCpltCallback(void);
void AUDIO_I2S_TxHalfCpltCallback(void);



