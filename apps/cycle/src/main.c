#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"



void  init_gpio(EXINF exinf)
{
    RCC_AHB1ENR |= (1 << 0); 
    RCC_AHB1ENR |= (1<<1); 



    GPIOB_MODER &= ~(0b11 << (5 * 2));   // 入力モード
    GPIOB_PUPDR &= ~(0b11 << (5 * 2));   // PUPDR初期化
    GPIOB_PUPDR |=  (0b01 << (5 * 2));   // プルアップ

    GPIOA_MODER &= ~(0b11 << (9 * 2));
    GPIOA_MODER |= (0b01 << (9*2));


    act_tsk(SW_TASK);
}


void led_flashing(EXINF exinf)
{


        GPIOA_ODR ^= (1 << 9);
        if(GPIOA_ODR & (1<<9))
        {
            syslog(LOG_NOTICE, "LED ON");
        }else{
            syslog(LOG_NOTICE, "LED OFF");
        }
        dly_tsk(5000);
    

    ext_tsk();
}


void sw_task(EXINF exinf)
{
   
    uint8_t prev = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
    bool_t currLedState = false;
    while(1)
    {
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
        if (prev == 1 && curr == 0)
        {
            if(currLedState)
            {
                sta_cyc(MY_CYC_LED_FLUSH);
            }else{
                stp_cyc(MY_CYC_LED_FLUSH);
            }
 
            currLedState = !currLedState;
        }
        prev =curr;
        dly_tsk(10000);
    }


    ext_tsk();
}