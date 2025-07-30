
#include <kernel.h>
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"


void init(EXINF exinf)
{

    RCC_AHB1ENR |= (1 << 0); 
    RCC_AHB1ENR |= (1 << 1); 


    
    GPIOA_MODER &= ~(0b11 << (9 * 2));
    GPIOA_MODER |= (0b01 << (9*2));

    GPIOA_MODER &= ~(0b11 << (5 * 2));      // 入力モード（0b00）
    GPIOA_PUPDR &= ~(0b11 << (5 * 2));      // プル設定を一度クリア
    GPIOA_PUPDR |=  (0b01 << (5 * 2));      // プルアップ（0b01）


    GPIOB_MODER &= ~(0b11 << (5 * 2));
    GPIOB_PUPDR |= (0b01 << (5*2));





    act_tsk(LED_TASK);
    act_tsk(SW_TASK);


}