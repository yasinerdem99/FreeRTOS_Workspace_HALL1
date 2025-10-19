/*
 * maxrefdes24.c
 *
 *  Created on: Oct 15, 2025
 *      Author: stj.yerdem
 *  @brief MAXREFDES24 4-CH Analog Output Module Driver
 *  @description Manages communication and output control for
 *               MAX5134 (DAC) and MAX15500 (current driver)
 */



#include "maxrefdes24.h"
#include "maxrefdes24_spi_stm.h" // STM32 HAL SPI/GPIO fonksiyonları



// ------------------------------
// Yardımcı Fonksiyon: DAC Code
// ------------------------------
static uint16_t max24_convertToDacCode(float current_mA, float range_mA)
{
    float ratio = (current_mA + range_mA) / (2 * range_mA);
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;
    return (uint16_t)(ratio * 0xFFFF);
}

// ------------------------------
// Cihaz Başlatma
// ------------------------------


// ------------------------------
// SPI Transfer
// ------------------------------
MAX_StatusTypeDef max24_xfer(MAXREFDES24_Device *dev, uint8_t *tx, uint8_t *rx, uint16_t len)
{
    max24_spi_select(dev->cs_dac_port, dev->cs_dac_pin);
    MAX_StatusTypeDef status = max24_spi_xfer(dev->hspi, tx, rx, len);
    max24_spi_deselect(dev->cs_dac_port, dev->cs_dac_pin);
    return status;
}

// ------------------------------
// Akım Ayarlama
// ------------------------------
// -------------------------------------
// Çok Kanallı Akım Ayarı (CH0..CH3)
// -------------------------------------
MAX_StatusTypeDef max24_setChannelCurrent(MAXREFDES24_Device *dev, uint8_t channel, float current_mA)
{
    if (channel > 3)
        return MAX_ERROR;

    uint16_t dacValue = max24_convertToDacCode(current_mA, 20.0f); // ±20mA range
    uint8_t txData[3];
    uint8_t rxData[3];

    // MAX5134 komut formatı: 0x30 | channel
    txData[0] = 0x30 | (channel & 0x03);
    txData[1] = (dacValue >> 8) & 0xFF;
    txData[2] = (dacValue) & 0xFF;

    max24_spi_select(dev->cs_dac_port, dev->cs_dac_pin);
    MAX_StatusTypeDef status = max24_spi_xfer(dev->hspi, txData, rxData, 3);
    max24_spi_deselect(dev->cs_dac_port, dev->cs_dac_pin);

    return status;
}

// -------------------------------------
// DC/DC (MAX15500) ENABLE
// -------------------------------------
MAX_StatusTypeDef max24_enableOutput(MAXREFDES24_Device *dev)
{
    /* MAX15500 Enable/Config komutu (Current Mode, ±20mA) */
    uint8_t tx[3];
    uint8_t rx[3];

    /* MAX15500 Control Register:
     * Datasheet: CH enable + current mode + normal operation
     *
     * Örnek konfigürasyon (3 byte):
     * 0x01 = Control Register write
     * 0x00 = Safe defaults / channel mask (şimdilik tüm kanallar açık)
     * 0x01 = Mode: Current Mode + Enable
     */
    tx[0] = 0x01;  // CONTROL REGISTER WRITE
    tx[1] = 0x00;  // Tüm kanallar olarak açık (safe)
    tx[2] = 0x01;  // Current Mode + Enable

    max24_spi_select(dev->cs_dc_port, dev->cs_dc_pin);
    MAX_StatusTypeDef status = max24_spi_xfer(dev->hspi, tx, rx, 3);
    max24_spi_deselect(dev->cs_dc_port, dev->cs_dc_pin);

    return status;
}

