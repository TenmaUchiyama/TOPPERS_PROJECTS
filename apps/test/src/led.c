#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"




void led_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "LED TASK START"); 

    

    while(1)
    {
        FLGPTN actual_flg;

        wai_flg(MY_FLG, LED_ON, TA_WMUL, &actual_flg); 
        syslog(LOG_NOTICE, "FLAG UP");
        GPIOA_ODR ^= (1 << 9);
        clr_flg(MY_FLG , 0x00);
        dly_tsk(1000000);
    }

    ext_tsk();
}