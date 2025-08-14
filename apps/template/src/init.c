#include <kernel.h>
#include "main.h"
#include "stm32f4xx.h"

void init_gpio(EXINF exinf)
{
    syslog(LOG_NOTICE, "GPIO INIT");

    
    // GPIOA クロックを有効化
    RCC->AHB1ENR |= (1 << 0);



    GPIOA->MODER &= ~(0b11 << (9*2));  // ピン9を入力モードに設定
    GPIOA->MODER |= (0b01 << (9*2));   // ピン9を出力モードに設定

    GPIOB->MODER &= ~(0b11 << (5*2));  // ピン5を入力モードに設定
    GPIOB->PUPDR &= ~(0b11 << (5*2));  // ピン5をプルダウンに設定
    GPIOB->PUPDR |= (0b01 << (5*2));   // ピン5をプルアップに設定







}


