/*
 * maxrefdes24.c
 *
 * Created on: Oct 15, 2025
 * Author: stj.yerdem
 * @brief MAXREFDES24 4-CH Analog Output Module Driver
 * @description Manages communication and output control for
 * MAX5134 (DAC) and MAX15500 (current driver).
 * This version uses STM32 HAL functions directly.
 */

#include "maxrefdes24.h"
// Artık "maxrefdes24_spi_stm.h" dosyasına ihtiyacımız yok.

/**
 * @brief Sürücü handle'ını donanım bilgileriyle başlatır.
 */
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

    // Başlangıçta tüm CS pinlerini pasif yap (HIGH)
    HAL_GPIO_WritePin(dev->cs_dac_port, dev->cs_dac_pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(dev->cs_dc_port, dev->cs_dc_pin, GPIO_PIN_SET);
}

/**
 * @brief Akım değerini (mA) 16-bit DAC koduna dönüştürür.
 */
static uint16_t max24_convertToDacCode(float current_mA, float range_mA)
{
    float ratio = (current_mA + range_mA) / (2.0f * range_mA);
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;
    return (uint16_t)(ratio * 0xFFFF);
}

/**
 * @brief MAX15500 çıkışını Bipolar ±20mA modunda etkinleştirir.
 */
HAL_StatusTypeDef max24_enableOutput(MAXREFDES24_Device *dev)
{
    uint8_t tx_buffer[2];

    /* * MAX15500 Kontrol Kaydı (Datasheet Tablo 5 & 6)
     * Komut: 0x0888 -> Adres[13:11]=001 (Write Config), Mod[9:7]=001 (Bipolar ±20mA), Termal[3]=1 (AÇIK)
     */
    tx_buffer[0] = 0x08;
    tx_buffer[1] = 0xF8;

    // MAX15500 CS pinini aktif et (LOW)
    HAL_GPIO_WritePin(dev->cs_dc_port, dev->cs_dc_pin, GPIO_PIN_RESET);

    // Komutu SPI üzerinden gönder (Sadece yazma)
    HAL_StatusTypeDef status = HAL_SPI_Transmit(dev->hspi, tx_buffer, 2, HAL_MAX_DELAY);

    // MAX15500 CS pinini pasif yap (HIGH)
    HAL_GPIO_WritePin(dev->cs_dc_port, dev->cs_dc_pin, GPIO_PIN_SET);

    return status;
}

/**
 * @brief Belirtilen kanala istenen akım değerini ayarlar.
 */
HAL_StatusTypeDef max24_setChannelCurrent(MAXREFDES24_Device *dev, uint8_t channel, float current_mA)
{
    if (channel > 3) {
        return HAL_ERROR; // Geçersiz kanal numarası
    }

    uint16_t dacValue = max24_convertToDacCode(current_mA, 20.0f); // ±20mA aralığı
    uint8_t tx_buffer[3];

    // MAX5134 "Write-through" komutunu ve veriyi oluştur
    tx_buffer[0] = 0x30 | (1 << channel);
    tx_buffer[1] = (dacValue >> 8) & 0xFF;
    tx_buffer[2] = (dacValue) & 0xFF;

    // MAX5134 CS pinini aktif et (LOW)
    HAL_GPIO_WritePin(dev->cs_dac_port, dev->cs_dac_pin, GPIO_PIN_RESET);

    // Komutu ve veriyi SPI üzerinden gönder (Sadece yazma)
    HAL_StatusTypeDef status = HAL_SPI_Transmit(dev->hspi, tx_buffer, 3, HAL_MAX_DELAY);

    // MAX5134 CS pinini pasif yap (HIGH)
    HAL_GPIO_WritePin(dev->cs_dac_port, dev->cs_dac_pin, GPIO_PIN_SET);



    return status;
}
