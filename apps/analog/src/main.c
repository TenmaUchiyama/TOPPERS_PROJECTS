#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"
#include "stm32f4xx.h"






void set_rgb(uint8_t r_percent, uint8_t g_percent, uint8_t b_percent)
{
    uint32_t arr1 = TIM1->ARR + 1; // TIM1: 青
    uint32_t arr3 = TIM3->ARR + 1; // TIM3: 赤・緑

    TIM3->CCR1 = (arr3 * r_percent) / 100; // 赤  = TIM3_CH1 (PB4)
    TIM3->CCR2 = (arr3 * g_percent) / 100; // 緑  = TIM3_CH2 (PC7)
    TIM1->CCR2 = (arr1 * b_percent) / 100; // 青  = TIM1_CH2 (PA9)
}


static inline uint16_t adc_read_once(uint8_t ch)
{

    loc_mtx(ADC_MTX);
    // 変換するチャンネルをセット
    ADC1->SQR3 = (uint32_t)ch & 0x1F;   // SQ1 = ch

    // 変換開始
    ADC1->CR2 |= ADC_CR2_SWSTART;

    // 完了待ち（EOCが立つまで）
    while (!(ADC1->SR & ADC_SR_EOC)) {}
    unl_mtx(ADC_MTX);

    // 値取得（読むとEOCはクリアされる）
    return (uint16_t)ADC1->DR;          // 0..4095
}

void potA_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "DIM TASK START");
    // ※どこかの初期化で blue_pwm_init_TIM1_PA9(); を1回呼んでおくこと

    while (1) {
        uint16_t raw = adc_read_once(0); // A0
        uint8_t percent = (uint8_t)(raw * 100 / 4095);
        set_rgb(0, 0, percent);
        dly_tsk(1000);// 10ms〜適宜
    }

    ext_tsk();
}

void potB_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "POT B TASK START");

    while(1)
    {
        uint16_t raw = adc_read_once(1); 
        uint8_t percent = (uint8_t)(raw * 100 / 4095); 
        set_rgb(0,percent, 0);
        dly_tsk(1000);
    }
}