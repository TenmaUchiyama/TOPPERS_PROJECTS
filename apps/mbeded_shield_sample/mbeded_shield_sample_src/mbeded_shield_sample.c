#include <kernel.h>
#include <t_syslog.h>
#include "REG.h"
#include "mbeded_shield_sample.h"
#include "kernel_cfg.h"



void led_task(EXINF exinf)
{
    
 

    slp_tsk();




    GPIOA_ODR &= ~(1 << 9);  

    
    ext_tsk();
}

void sw_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "USER BTN TASK START");


    

    uint8_t prev = 0;  // ボタン離された状態

    while (1)
    {
        // ④ PC13の状態を読む
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0; 

        // ⑤ 押された瞬間だけログを出す
        if (prev == 1 && curr == 0)
        {
            syslog(LOG_NOTICE, "USER BUTTON PRESSED");
            wup_tsk(LED_TASK);
        }

        prev = curr;

        dly_tsk(100000); // 約10ms待機
    }

    ext_tsk();
}
