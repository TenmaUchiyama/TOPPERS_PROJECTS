#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"



void  init_gpio(EXINF exinf)
{
     // GPIOA と ADC1 のクロックを有効化
    RCC_AHB1ENR |= (1 << 0);   // GPIOAEN
    RCC_APB2ENR |= (1 << 8);   // ADC1EN

    // PA0, PA1 をアナログモードに設定
    GPIOA_MODER |= (0b11 << (0 * 2));  // PA0
    GPIOA_MODER |= (0b11 << (1 * 2));  // PA1

    // ADC ON
    ADC1_CR2 |= ADC_CR2_ADON;

   syslog(LOG_NOTICE, "gpio initialized for ADC");
}


uint16_t read_adc(uint8_t channel)
{
     ADC1_SQR3 = channel;           // ADCチャネル選択
    ADC1_CR2 |= ADC_CR2_SWSTART;   // 変換開始

    while (!(ADC1_SR & ADC_SR_EOC)); // 終了待ち

    return (uint16_t)ADC1_DR;
}

void adc_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "adc_task started");

    init_gpio(0);  // ← ATT_INI で呼ばれないときのために一時的にここで呼ぶ

    while (1) {
        uint16_t val0 = read_adc(0); // A0: PA0
        uint16_t val1 = read_adc(1); // A1: PA1

        syslog(LOG_NOTICE, "ADC A0 (PA0): %u, A1 (PA1): %u", val0, val1);

        dly_tsk(500000); // 500ms wait
    }
}
