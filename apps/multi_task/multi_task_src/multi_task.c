#include <kernel.h>
#include <t_syslog.h>
#include "multi_task.h"
#include "REG.h"


void led_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "LED TASK STARTED");
    RCC_AHB1ENR |= (1 << 0);


    GPIOA_MODER &= ~(0x11 << 5); 
    GPIOA_MODER |= (0x01 << 5);



    while(1)
    {
        
        GPIOA_ODR ^= (1 << 5);
        dly_tsk(1000000);
    }


    ext_tsk();
};



void sw_task(EXINF exinf)
{

    syslog(LOG_NOTICE, "SWITCH TASK STARTED");
    RCC_AHB1ENR |= (1 << 2);  // GPIOCを有効化

    GPIOC_MODER &= ~(0x3 << (2*13));  // PC13を入力モードに設定
    uint8_t prev = (GPIOC_IDR & (1 << 13)) ? 1 : 0; 

    GPIOC_PUPDR &= ~(0x3 << (2*13));  // 13番ピンのPUPDRクリア
    GPIOC_PUPDR |=  (0x1 << (2*13));  // 01: プルアップ有効
   while(1){
    uint8_t curr = (GPIOC_IDR & (1 << 13)) ? 1 : 0; 
    uint32_t idr_value = GPIOC_IDR;
    syslog(LOG_NOTICE, "BTN STATE: %d, IDR: 0x%08X, PC13 bit: %d", curr, idr_value, (idr_value >> 13) & 1);
    if(!curr && prev)  // 立ち下がりエッジ（ボタンが押された）
    { 
        syslog(LOG_NOTICE, "BTN PRESSED");
    }

    prev = curr;
        dly_tsk(10000);
    }

    ext_tsk();
}
