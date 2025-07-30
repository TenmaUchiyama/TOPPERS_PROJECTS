#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "../include/main.h"
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