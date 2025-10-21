/*
 * maxrefdes24.h
 *
 * Created on: Oct 15, 2025
 * Author: stj.yerdem
 * @brief Header file for MAXREFDES24 4-CH Analog Output Module Driver
 * (Direct HAL implementation)
 */

#ifndef INC_MAXREFDES24_H_
#define INC_MAXREFDES24_H_

#include "stm32f4xx_hal.h" // Kullandığın MCU serisine göre (F1, F4, vb.) bu satırı ayarla



/**
 * @brief Sürücünün ihtiyaç duyduğu donanım bilgilerini tutan yapı.
 */
typedef struct {
    SPI_HandleTypeDef *hspi;          // Kullanılacak SPI handle'ı
    GPIO_TypeDef      *cs_dac_port;   // MAX5134 (DAC) için CS portu
    uint16_t          cs_dac_pin;     // MAX5134 (DAC) için CS pini
    GPIO_TypeDef      *cs_dc_port;    // MAX15500 (Driver) için CS portu
    uint16_t          cs_dc_pin;      // MAX15500 (Driver) için CS pini
} MAXREFDES24_Device;

/**
 * @brief Analog çıkış sürücüsünü başlatır ve donanım bilgilerini kaydeder.
 * @param dev: Sürücü handle'ı (pointer).
 * @param hspi: Kullanılacak SPI handle'ı.
 * @param cs_dac_port: MAX5134 CS portu.
 * @param cs_dac_pin: MAX5134 CS pini.
 * @param cs_dc_port: MAX15500 CS portu.
 * @param cs_dc_pin: MAX15500 CS pini.
 */
void max24_init(MAXREFDES24_Device *dev,
                SPI_HandleTypeDef *hspi,
                GPIO_TypeDef *cs_dac_port, uint16_t cs_dac_pin,
                GPIO_TypeDef *cs_dc_port, uint16_t cs_dc_pin);

/**
 * @brief MAX15500 çıkış sürücüsünü Bipolar ±20mA modunda etkinleştirir.
 * @param dev: Başlatılmış sürücü handle'ı (pointer).
 * @retval HAL_StatusTypeDef: HAL_OK (başarılı) veya HAL_ERROR.
 */
HAL_StatusTypeDef max24_enableOutput(MAXREFDES24_Device *dev);

/**
 * @brief Belirtilen kanala istenen akım değerini ayarlar (MAX5134 DAC üzerinden).
 * @param dev: Başlatılmış sürücü handle'ı (pointer).
 * @param channel: Ayarlanacak kanal (0, 1, 2, veya 3).
 * @param current_mA: Ayarlanacak akım değeri (örn: 10.5, -5.0). ±20mA aralığında olmalı.
 * @retval HAL_StatusTypeDef: HAL_OK (başarılı) veya HAL_ERROR.
 */
HAL_StatusTypeDef max24_setChannelCurrent(MAXREFDES24_Device *dev, uint8_t channel, float current_mA);

#endif /* INC_MAXREFDES24_H_ */
