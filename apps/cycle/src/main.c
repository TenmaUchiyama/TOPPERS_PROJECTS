#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"




void init_gpio(EXINF exinf)
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
    syslog(LOG_NOTICE, "LED FLASING"); 




    GPIOA_ODR ^= (1<<9); 

    if(GPIOA_ODR & (1 << 9))
    {
        syslog(LOG_NOTICE, "LED ON"); 
    }else{
        syslog(LOG_NOTICE, "LED OFF");
    }
   



  
}


void sw_task(EXINF exinf)
{
    RCC_AHB1ENR |= (1<<1); 
    GPIOB_MODER &= ~(0b11 << (5 * 2));   // 入力モード
    GPIOB_PUPDR &= ~(0b11 << (5 * 2));   // PUPDR初期化
    GPIOB_PUPDR |=  (0b01 << (5 * 2));   // プルアップ


    uint8_t prev = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
    bool_t crrBtn = false;

    while(1)
    {
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
        if (prev == 1 && curr == 0)
        {
            syslog(LOG_NOTICE, "Button Pressed"); 
            
            crrBtn = !crrBtn; 

            if(crrBtn)
            {
                syslog(LOG_NOTICE, "TIMER START");
                sta_cyc(CYC_LED_FLASHING);
            }else{

                syslog(LOG_NOTICE, "TIMER STOP");
                stp_cyc(CYC_LED_FLASHING);
            }


        }
        prev =curr;
        dly_tsk(10000);
    }
}