#include "uart_cmd.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define RX_BUF_SIZE  64

static UART_HandleTypeDef *s_huart = NULL;
static char rx_buf[RX_BUF_SIZE];

/* Live Expression değişkenleri */
volatile int g_cmd_channel = -1;
volatile int g_cmd_value   =  0;
volatile uint8_t g_cmd_valid = 0;
volatile uint8_t g_cs_calc = 0;
volatile uint8_t g_cs_recv = 0;

/* --- Dahili yardımcılar --- */

static uint8_t UART_ReadLine_Blocking(char *buf, uint16_t maxLen)
{
    uint16_t i = 0;
    char c;
    while (i < (maxLen - 1))
    {
        /* 1 byte blocking alım */
        if (HAL_UART_Receive(s_huart, (uint8_t *)&c, 1, HAL_MAX_DELAY) != HAL_OK)
            continue;

        buf[i++] = c;
        if (c == '\n'|| c == '\r') break;  /* CRLF bekliyoruz; LF gelince satırı bitir */
    }
    buf[i] = '\0';
    return (uint8_t)i;
}

static uint8_t checksum_xor(const char *p)
{
    uint8_t cs = 0;
    while (*p) cs ^= (uint8_t)(*p++);
    return cs;
}

static void process_packet(const char *msg)
{
    /* Ör:  $SCCON,X,Y*hh\r\n  */
    const char *start = strchr(msg, '$');
    const char *star  = strchr(msg, '*');
    if (!start || !star || star <= start)
    {
        g_cmd_valid = 0;
        return;
    }

    /* payload = '$' ile '*' arasındaki kısım, '$' dahil değil */
    char payload[32];
    uint16_t len = (uint16_t)(star - (start + 1));

    if (len >= sizeof(payload))
    {
    	g_cmd_valid = 0; return;
    }

    strncpy(payload, start + 1, len);
    payload[len] = '\0';

    /* '*' sonrası 2 hex byte checksum (hh) */
    g_cs_recv = (uint8_t) strtol(star + 1, NULL, 16);
    g_cs_calc = checksum_xor(payload);

    if (g_cs_recv != g_cs_calc) {
        g_cmd_valid = 0;
        return;
    }

    /* ---- CHECKSUM OK → strtok ile parçala ---- */
    char temp[32];
    strncpy(temp, payload, sizeof(temp) - 1);
    temp[sizeof(temp)-1] = '\0';

    char *cmd = strtok(temp, ",");
    char *x   = strtok(NULL, ",");
    char *y   = strtok(NULL, ",");

    if (!cmd || !x || !y) { g_cmd_valid = 0; return; }

    /* Komut adı bekleneni mi? */
    if (strcmp(cmd, "SCCON") != 0) { g_cmd_valid = 0; return; }

    int ch = atoi(x);
    int val = atoi(y);

    /* Basit sınama (gerekirse sıkılaştır) */
    if (ch < 0 || ch > 7) { g_cmd_valid = 0; return; }

    g_cmd_channel = ch;
    g_cmd_value   = val;
    g_cmd_valid   = 1;
}

/* --- Dış arayüz --- */

void UartCmd_Init(UART_HandleTypeDef *huart)
{
    s_huart = huart;
    g_cmd_channel = -1;
    g_cmd_value = 0;
    g_cmd_valid = 0;
    g_cs_calc = 0;
    g_cs_recv = 0;
}

void UartCmd_Task(void)
{
    if (s_huart == NULL) return;

    /* Bir satır oku (CR/LF ile biten) */
    uint8_t n = UART_ReadLine_Blocking(rx_buf, RX_BUF_SIZE);
    if (n > 0)
    {
        process_packet(rx_buf);
    }
}

/* --- (Opsiyonel) printf yönlendirme --- */
int __io_putchar(int ch)
{
    if (s_huart) {
        (void)HAL_UART_Transmit(s_huart, (uint8_t*)&ch, 1, 10);
    }
    return ch;
}

void Retarget_InitForPrintf(UART_HandleTypeDef *huart)
{
    s_huart = huart; /* printf için aynı huart’ı kullanıyoruz */
}


