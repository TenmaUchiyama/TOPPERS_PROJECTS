#include "mbeded_shield_sample.h";
#include "REG.h";
#include <kernel.h>


extern void init_gpio_task(EXINF exinf)
{
   // Aを有効化
   RCC_AHB1ENR |= (1 << 0); 
   RCC_AHB1ENR |= (1 << 1); 

   //Aを書き込み用にする
   GPIOA_MODER &= ~(0b11 << (9 * 2)); 
   GPIOA_MODER |= (0b01 << (9*2)); 
   GPIOA_ODR |= (1 << 9);


   GPIOB_MODER &= ~(0b11 << (5 * 2));  
   GPIOB_PUPDR &= ~(0b11 << (5 * 2));  







}