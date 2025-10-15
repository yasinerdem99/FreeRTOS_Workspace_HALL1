/*
 * maxrefdes24.h
 *
 *  Created on: Oct 15, 2025
 *      Author: stj.yerdem
 */

#ifndef SRC_MAXREFDES24_H_
#define SRC_MAXREFDES24_H_

#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

HAL_StatusTypeDef max24_SetCurrent_Spi1(float current_mA);
HAL_StatusTypeDef max24_SetCurrent_Spi2(float current_mA);
HAL_StatusTypeDef max24_xfer1(uint8_t *tx,uint8_t *rx, uint16_t len);
HAL_StatusTypeDef max24_xfer2(uint8_t *tx,uint8_t *rx, uint16_t len);


#endif /* SRC_MAXREFDES24_H_ */
