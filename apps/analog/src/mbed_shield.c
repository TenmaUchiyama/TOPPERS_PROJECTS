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

