#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"




void  init(EXINF exinf)
{
    RCC_AHB1ENR |= (1 << 0); 
    RCC_AHB1ENR |= (1<<1); 



    GPIOB_MODER &= ~(0b11 << (5 * 2));   // 入力モード
    GPIOB_PUPDR &= ~(0b11 << (5 * 2));   // PUPDR初期化
    GPIOB_PUPDR |=  (0b01 << (5 * 2));   // プルアップ

    GPIOA_MODER &= ~(0b11 << (9 * 2));
    GPIOA_MODER |= (0b01 << (9*2));


    act_tsk(LED_TASK);
    act_tsk(SW_TASK);
}

void led_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "LED TASK START"); 



    while(1)
    {
        wai_sem(MY_SEM);
        GPIOA_ODR ^= (1 << 9);
        sig_sem(MY_SEM);
        dly_tsk(500000);
    }

    ext_tsk();
}


void sw_task(EXINF exinf)
{
    


    uint8_t prev = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
    while(1)
    {
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
        if (prev == 1 && curr == 0)
        {
            wai_sem(MY_SEM); 
            syslog(LOG_NOTICE, "Button Pressed"); 
            GPIOA_ODR &= ~(1 << 9);
            dly_tsk(3000000);
            GPIOA_ODR |= (1 << 9);
            sig_sem(MY_SEM);

        }
        prev =curr;
        dly_tsk(10000);
    }
}