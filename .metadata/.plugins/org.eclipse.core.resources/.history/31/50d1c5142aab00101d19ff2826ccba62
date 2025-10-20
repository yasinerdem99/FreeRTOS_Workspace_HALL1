/*
 * maxrefdes24_spi_stm.c
 *
 *  Created on: Oct 16, 2025
 *      Author: stj.yerdem
 */





#include "stm32f4xx_hal.h"
#include "maxrefdes24_spi_stm.h"

void max24_spi_select(void *port, uint16_t pin)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)port, pin, GPIO_PIN_RESET);
}

void max24_spi_deselect(void *port, uint16_t pin)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)port, pin, GPIO_PIN_SET);
}

int max24_spi_xfer(void *hspi, uint8_t *tx, uint8_t *rx, uint16_t len)
{
    return HAL_SPI_TransmitReceive((SPI_HandleTypeDef *)hspi, tx, rx, len, HAL_MAX_DELAY);
}


void max24_init(MAXREFDES24_Device *dev,
                SPI_HandleTypeDef *hspi,
                GPIO_TypeDef *cs_dac_port, uint16_t cs_dac_pin,
                GPIO_TypeDef *cs_dc_port, uint16_t cs_dc_pin)
{
    dev->hspi = hspi;
    dev->cs_dac_port = cs_dac_port;
    dev->cs_dac_pin = cs_dac_pin;
    dev->cs_dc_port = cs_dc_port;
    dev->cs_dc_pin = cs_dc_pin;
}

