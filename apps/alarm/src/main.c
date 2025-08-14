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


        GPIOA_ODR &= ~(1<<9); // Light Up
     


}


void sw_task(EXINF exinf)
{
   syslog(LOG_NOTICE, "SW TASKSTARTED");
    uint8_t prev = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
    bool_t currLedState = false;
    while(1)
    {
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
        if (prev == 1 && curr == 0)
        {
            syslog(LOG_NOTICE, "Btn pressed");
          
              if(GPIOA_ODR & (1 << 9)){
                
              syslog(LOG_NOTICE, "Starting Led");
                GPIOA_ODR &= ~(1 << 9); //ON
                    stp_alm(MY_ALM);
               }else{
                
              syslog(LOG_NOTICE, "Stopping Led");
                    GPIOA_ODR |= (1 << 9); //OFF
                    sta_alm(MY_ALM,5000000);

               }
 
            currLedState = !currLedState;
        }
        prev =curr;
        dly_tsk(10000);
    }


    ext_tsk();
}