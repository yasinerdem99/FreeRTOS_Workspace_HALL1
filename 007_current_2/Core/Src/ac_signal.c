/*
 * ac_signal.c
 */

#include "ac_signal.h"
#include <math.h> // sinf() ve M_PI için

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

// Sinüs dalgasının pürüzsüzlüğü için nokta sayısı.
// 128 (2'nin kuvveti) seçmek, modulo (%) işlemi yerine bitwise AND (&)
// kullanmamızı sağlayarak ISR içinde hız kazandırır.
#define SINE_LUT_SIZE 128

/* --- Statik (dahili) değişkenler --- */

static TIM_HandleTypeDef    *s_htim_ac = NULL; // AC Timer Handle
static MAXREFDES24_Device   *s_dev_ac  = NULL; // AC Çıkış Cihazı
static uint8_t              s_ch_ac  = 0;    // AC Çıkış Kanalı (0-3)

// Sinüs Arama Tablosu (LUT)
static float s_sine_lut[SINE_LUT_SIZE];

// ISR tarafından kullanılan global değişkenler
static volatile uint32_t s_sine_index = 0;
static volatile float    s_ac_amplitude_ma = 0.0f;

/* --- Fonksiyon Gövdeleri --- */

void AC_Signal_Init(TIM_HandleTypeDef *htim, MAXREFDES24_Device *dev, uint8_t channel)
{
    s_htim_ac = htim;
    s_dev_ac  = dev;
    s_ch_ac   = channel;

    // Sinüs arama tablosunu (-1.0 ile +1.0 arasında) doldur
    for (int i = 0; i < SINE_LUT_SIZE; i++)
    {
        s_sine_lut[i] = sinf(2.0f * M_PI * (float)i / (float)SINE_LUT_SIZE);
    }

    AC_Signal_Stop(); // Başlangıçta durduğundan ve çıkışın 0 olduğundan emin ol
}

void AC_Signal_Start(float amplitude_mA, uint32_t frequency_hz)
{
    // Önce timer'ı durdur
    HAL_TIM_Base_Stop_IT(s_htim_ac);

    s_ac_amplitude_ma = amplitude_mA;

    // Eğer frekans 0 ise veya genlik 0 ise, sinyali durdur ve çık
    if (frequency_hz == 0 || amplitude_mA == 0.0f)
    {
        AC_Signal_Stop();
        return;
    }

    // Timer'ın kesme frekansını hesapla
    // (İstenen Frekans) * (Tablo Boyutu) = Güncelleme Frekansı
    uint32_t update_freq_hz = frequency_hz * SINE_LUT_SIZE;

    /* --- Timer Periyodunu Dinamik Hesaplama --- */

    // Timer'ın bağlı olduğu APB veriyolu saatini al (örn: APB1 için PCLK1)
    // TIM6, APB1 üzerindedir.
    uint32_t pclk = HAL_RCC_GetPCLK1Freq();
    uint32_t timer_clk = pclk;

    // Eğer APB prescaler (PPRE1) 1'den farklıysa, timer saati 2*PCLK olur.
    if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1)
    {
        timer_clk *= 2;
    }

    // Timer'ın sayması gereken toplam tick sayısı
    // (Timer Saati) / (Güncelleme Frekansı)
    uint32_t period_ticks = timer_clk / update_freq_hz;

    // En iyi PSC ve ARR değerlerini bul
    // (PSC+1) * (ARR+1) = period_ticks
    uint16_t psc = (uint16_t)(period_ticks / 65536); // Önce prescaler'ı bul
    uint16_t arr = (uint16_t)((period_ticks / (psc + 1)) - 1); // Sonra periyodu bul

    // Yeni PSC ve ARR değerlerini timer'a yükle
    __HAL_TIM_SET_PRESCALER(s_htim_ac, psc);
    __HAL_TIM_SET_AUTORELOAD(s_htim_ac, arr);

    /* --- Timer'ı Başlat --- */

    s_sine_index = 0;                     // İndeksi sıfırla
    __HAL_TIM_SET_COUNTER(s_htim_ac, 0);  // Sayacı sıfırla

    // Timer'ı kesme modunda başlat
    HAL_TIM_Base_Start_IT(s_htim_ac);
}

void AC_Signal_Stop(void)
{
    if (s_htim_ac) {
        HAL_TIM_Base_Stop_IT(s_htim_ac);
    }

    s_ac_amplitude_ma = 0.0f;
    s_sine_index = 0;

    // Çıkışı 0mA'e ayarla (güvenlik için)
    if (s_dev_ac) {
        max24_setChannelCurrent(s_dev_ac, s_ch_ac, 0.0f);
    }
}

/**
 * @brief Bu fonksiyon, Timer kesmesi tarafından tetiklenir.
 */
void AC_Signal_Timer_ISR_Handler(void)
{
    // Hata kontrolü veya sinyal durmuşsa
    if (s_dev_ac == NULL || s_ac_amplitude_ma == 0.0f) {
        return;
    }

    // 1. Sinüs tablosundan mevcut değeri al (-1.0 ila 1.0)
    float sine_val = s_sine_lut[s_sine_index];

    // 2. Değeri istenen genlik ile ölçekle
    float current_mA = sine_val * s_ac_amplitude_ma;

    // 3. DAC'a (MAX24) değeri yaz
    //    Not: Bu bir kesme (ISR) içinde çağrılır. max24_setChannelCurrent'in
    //    içindeki HAL_SPI_Transmit'in bloking (HAL_MAX_DELAY) OLMAMASI gerekir.
    //    Eğer SPI DMA ile değilse, bu kesme SPI tamamlanana kadar bloke olacaktır.
    //    Düşük SPI hızlarında bu durum, sinyal zamanlamasını bozabilir.
    //    Şimdilik çalıştığını varsayıyoruz.
    max24_setChannelCurrent(s_dev_ac, s_ch_ac, current_mA);

    // 4. Tablodaki bir sonraki indekse git
    //    SINE_LUT_SIZE (128) 2'nin kuvveti olduğu için s_sine_index % 128
    //    yerine (s_sine_index + 1) & 127 kullanabiliriz. (Daha hızlı)
    s_sine_index = (s_sine_index + 1) & (SINE_LUT_SIZE - 1);
}


