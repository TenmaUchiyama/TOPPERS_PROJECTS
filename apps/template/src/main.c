#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"




void led_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "LED TASK START"); 

    RCC_AHB1ENR |= (1 << 0); 


    GPIOA_MODER &= ~(0b11 << (9 * 2));
    GPIOA_MODER |= (0b01 << (9*2));

    while(1)
    {
        GPIOA_ODR ^= (1 << 9);
        dly_tsk(1000000);
    }

    ext_tsk();
}


void sw_task(EXINF exinf)
{
    RCC_AHB1ENR |= (1<<1); 
    GPIOB_MODER &= ~(0b11 << (5 * 2));   // 入力モード
    GPIOB_PUPDR &= ~(0b11 << (5 * 2));   // PUPDR初期化
    GPIOB_PUPDR |=  (0b01 << (5 * 2));   // プルアップ


    uint8_t prev = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
    while(1)
    {
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
        if (prev == 1 && curr == 0)
        {
            syslog(LOG_NOTICE, "Button Pressed"); 
        }
        prev =curr;
        dly_tsk(10000);
    }
}