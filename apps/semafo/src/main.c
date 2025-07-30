#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"

void init(EXINF exinf)
{
    RCC_AHB1ENR |= (1 << 0); 

    RCC_AHB1ENR |= (1<<1); 


    GPIOA_MODER &= ~(0b11 << (9 * 2));
    GPIOA_MODER |= (0b01 << (9*2));

    GPIOB_MODER &= ~(0b11 << (5 * 2));   // 入力モード
    GPIOB_PUPDR &= ~(0b11 << (5 * 2));   // PUPDR初期化
    GPIOB_PUPDR |=  (0b01 << (5 * 2));   // プルアップ
    

    act_tsk(TASKA);
    act_tsk(TASKB);
}


void task_a(EXINF exinf)
{
    syslog(LOG_NOTICE, "TASK A  START"); 

   

    while(1)
    {

        wai_sem(MY_SEM); 

        GPIOA_ODR ^= (1 << 9);

        sig_sem(MY_SEM);
        dly_tsk(500000);
    }

    ext_tsk();
}


void task_b(EXINF exinf)
{

    syslog(LOG_NOTICE, "TASK B  START"); 

    


    uint8_t prev = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
    while(1)
    {   
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
        if (prev == 1 && curr == 0)
        {

            wai_sem(MY_SEM); 
        
            GPIOA_ODR &= ~(1 << 9);
            dly_tsk(3000000);
            
            GPIOA_ODR |= (1 << 9);
            
            sig_sem(MY_SEM);
            
        }
        prev =curr;
        dly_tsk(100000);
    }
}