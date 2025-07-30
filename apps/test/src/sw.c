#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"


void sw_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "SW TASK START"); 

   


    uint8_t prev = (GPIOB_IDR & (1 << 5)) ? 1 : 0;

    while(1)
    {
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;
        if(!prev & curr)
        {
            syslog(LOG_NOTICE, "BUTTON PRESSED");
            set_flg(MY_FLG, LED_ON);
        }
        prev = curr;
        dly_tsk(1000);
    }

    ext_tsk();
}