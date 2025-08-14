#include <kernel.h>
#include <t_syslog.h> 
#include "kernel_cfg.h"
#include "main.h"
#include "REG.h"
#include "stm32f4xx.h"


void  init_gpio(EXINF exinf)
{

    //  syslog(LOG_NOTICE, "INIT_GPIO STARTED");
    RCC_AHB1ENR |= (1 << 0); 
    RCC_AHB1ENR |= (1<<1); 



    GPIOB_MODER &= ~(0b11 << (5 * 2));   // 入力モード
    GPIOB_PUPDR &= ~(0b11 << (5 * 2));   // PUPDR初期化
    GPIOB_PUPDR |=  (0b01 << (5 * 2));   // プルアップ

    GPIOA_MODER &= ~(0b11 << (9 * 2));
    GPIOA_MODER |= (0b01 << (9*2));


//     SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI5;  
//    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI5_PB;  

   EXTI->IMR |= EXTI_IMR_MR5;

EXTI->FTSR |= EXTI_FTSR_TR5;  // 下がりエッジ有効
EXTI->RTSR &= ~EXTI_RTSR_TR5; // 上がりエッジ無効
// 3. NVICでEXTI9_5割込みを有効化
ena_int(EXTI9_5_IRQn);
// NVIC_EnableIRQ(EXTI9_5_IRQn); 
    syslog(LOG_NOTICE, "GPIO initialized");

}



void exti_pb5_handler(void)
{
    if (EXTI->PR & EXTI_PR_PR5) {
        EXTI->PR |= EXTI_PR_PR5; // フラグをクリア
        GPIOA_ODR ^= (1 << 9);
        syslog(LOG_NOTICE, "PB5 interrupt!");
    }
}
