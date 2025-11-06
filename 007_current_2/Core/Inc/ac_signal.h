/*
 * ac_signal.h
 *
 * Created on: Nov 6, 2025
 * Author: stj.yerdem (ve Gemini)
 * @brief AC Sinus Sinyal Üreteci Modülü
 */

#ifndef INC_AC_SIGNAL_H_
#define INC_AC_SIGNAL_H_

#include "stm32f4xx_hal.h"  // Cihazına uygun HAL başlığını kullan
#include "maxrefdes24.h"

/**
 * @brief Sinüs sinyal üretecini başlatır.
 * * @param htim Sinyal üretimi için kullanılacak Timer handle (örn: &htim6)
 * @param dev Sinyalin çıkış yapılacağı MAXREFDES24 cihazı (örn: &dev2)
 * @param channel Sinyalin çıkış yapılacağı MAXREFDES24 kanalı (0-3)
 */
void AC_Signal_Init(TIM_HandleTypeDef *htim, MAXREFDES24_Device *dev, uint8_t channel);

/**
 * @brief Belirtilen genlik ve frekansta AC sinyal üretimini başlatır.
 * * @param amplitude_mA Sinyalin tepe genliği (örn: 10.0f -> ±10.0mA)
 * @param frequency_hz Sinyalin frekansı (örn: 100 -> 100 Hz)
 */
void AC_Signal_Start(float amplitude_mA, uint32_t frequency_hz);

/**
 * @brief AC sinyal üretimini durdurur ve çıkışı 0mA'e ayarlar.
 */
void AC_Signal_Stop(void);

/**
 * @brief Timer kesmesi (ISR) içinde çağrılacak olan handler.
 * @note Bu fonksiyonu doğrudan stm32f4xx_it.c içindeki ilgili ISR'den çağırın.
 */
void AC_Signal_Timer_ISR_Handler(void);


#endif /* INC_AC_SIGNAL_H_ */
