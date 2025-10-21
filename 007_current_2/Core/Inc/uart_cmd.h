#ifndef UART_CMD_H
#define UART_CMD_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Live Expression için izlemesi kolay globaller */
extern volatile int g_cmd_channel;   // 0..7
extern volatile int g_cmd_value;     // örn. 10000 -> 10 mA
extern volatile uint8_t g_cmd_valid; // 1: son paket OK, 0: fail
extern volatile uint8_t g_cs_calc;   // hesaplanan checksum
extern volatile uint8_t g_cs_recv;   // gelen checksum

/* Başlat (hangi UART ile çalışacağımızı ver) */
void UartCmd_Init(UART_HandleTypeDef *huart);

/* Sürekli çağır: satır oku + doğrula + parse et */
void UartCmd_Task(void);

/* (Opsiyonel) printf yönlendirme istersek bunu açarız */
void Retarget_InitForPrintf(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* UART_CMD_H */
