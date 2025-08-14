#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "Pins.h"
#include "stm32f4xx.h"





void led_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "LED TASK START");
    // ① ここで set_rgb を一度呼べば色は“出しっぱなし”になる（ハードが自動でPWM）
    // set_rgb(0, 200, 200);   // 白（各色100%）

    while (1) {
        // ② このループは必要なら色を更新するだけ（CPUはほぼ暇）
        // 例えばフェードしたいならここで値を少しずつ変える
        dly_tsk(100000); // 100msおき等
    }
}

void sw_task(EXINF exinf)
{
   
    syslog(LOG_NOTICE, "SW TASK START");
    
    uint8_t prev = (GPIOB->IDR & (1 << 5)) ? 1 : 0;
    while(1)
    {
        uint8_t curr = (GPIOB->IDR & (1 << 5)) ? 1 : 0;
        if (prev == 1 && curr == 0)
        {
            syslog(LOG_NOTICE, "Button Pressed"); 
        }
        prev =curr;
        dly_tsk(10000);
    }
}
