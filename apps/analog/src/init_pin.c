#include <kernel.h>
#include <t_syslog.h>
#include "main.h"
#include "stm32f4xx.h"
#include "REG.h"

void init_rcc(void)
{
    // GPIOクロック有効化
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // タイマークロック有効化
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // TIM1 (Blue LED)
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // TIM2 (Speaker)
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // TIM3 (Red, Green LED)

    // ADC1クロック有効化
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
}

void init_gpio(void)
{
    // ==== PWM出力ピン ====
    // PA9 (TIM1_CH2, Blue LED)
    GPIOA->MODER &= ~(3u << (9*2));
    GPIOA->MODER |=  (2u << (9*2));  // AF
    GPIOA->AFR[1] &= ~(0xFu << ((9-8)*4));
    GPIOA->AFR[1] |=  (0x1u << ((9-8)*4)); // AF1: TIM1_CH2

    // PB4 (TIM3_CH1, Red LED)
    GPIOB->MODER &= ~(3u << (4*2));
    GPIOB->MODER |=  (2u << (4*2));
    GPIOB->AFR[0] &= ~(0xFu << (4*4));
    GPIOB->AFR[0] |=  (0x2u << (4*4)); // AF2: TIM3_CH1

    // PC7 (TIM3_CH2, Green LED)
    GPIOC->MODER &= ~(3u << (7*2));
    GPIOC->MODER |=  (2u << (7*2));
    GPIOC->AFR[0] &= ~(0xFu << (7*4));
    GPIOC->AFR[0] |=  (0x2u << (7*4)); // AF2: TIM3_CH2

    // PB10 (TIM2_CH3, Speaker)
    GPIOB->MODER &= ~(3u << (10*2));
    GPIOB->MODER |=  (2u << (10*2));
    GPIOB->AFR[1] &= ~(0xFu << ((10-8)*4));
    GPIOB->AFR[1] |=  (0x1u << ((10-8)*4)); // AF1: TIM2_CH3

    // ==== 入力ボタン ====
    struct { GPIO_TypeDef* port; uint32_t pin; } btns[] = {
        {GPIOC, 0}, // RightBtn
        {GPIOA, 4}, // UpBtn
        {GPIOB, 5}, // CenterBtn
        {GPIOC, 1}, // LeftBtn
        {GPIOB, 0}  // DownBtn
    };
    for (int i=0;i<5;i++) {
        btns[i].port->MODER &= ~(3u << (btns[i].pin*2));
        btns[i].port->PUPDR &= ~(3u << (btns[i].pin*2));
        btns[i].port->PUPDR |=  (1u << (btns[i].pin*2)); // Pull-up
    }

    // ==== アナログ入力 ====
    // PA0 (ADC1_IN0), PA1 (ADC1_IN1)
    GPIOA->MODER |= (3u << (0*2)) | (3u << (1*2)); // Analog
    GPIOA->PUPDR &= ~((3u << (0*2)) | (3u << (1*2)));

    // ==== LCD制御ピン ====
    // PB6 (nCS)
    GPIOB->MODER &= ~(3u << (6*2));
    GPIOB->MODER |=  (1u << (6*2)); // Output

    // PA8 (A0)
    GPIOA->MODER &= ~(3u << (8*2));
    GPIOA->MODER |=  (1u << (8*2)); // Output

    // PA5 (SCK), PA7 (MOSI) → SPI
    GPIOA->MODER &= ~((3u << (5*2)) | (3u << (7*2)));
    GPIOA->MODER |=  ((2u << (5*2)) | (2u << (7*2)));
    GPIOA->AFR[0] &= ~((0xFu << (5*4)) | (0xFu << (7*4)));
    GPIOA->AFR[0] |=  ((0x5u << (5*4)) | (0x5u << (7*4))); // AF5: SPI1

    // PA6 (RESET)
    GPIOA->MODER &= ~(3u << (6*2));
    GPIOA->MODER |=  (1u << (6*2)); // Output
}

void init_tim(void)
{
    // ==== TIM1 (Blue LED) ====
    TIM1->PSC = 83;    // 84MHz / 84 = 1MHz
    TIM1->ARR = 999;   // 1kHz PWM
    TIM1->CCR2 = 0;
    TIM1->CCMR1 &= ~(7u << 12);
    TIM1->CCMR1 |=  (6u << 12) | (1u << 11);
    TIM1->CCER  |=  TIM_CCER_CC2E | TIM_CCER_CC2P;
    TIM1->BDTR  |=  TIM_BDTR_MOE;
    TIM1->CR1   |=  TIM_CR1_ARPE | TIM_CR1_CEN;
    TIM1->EGR    =  TIM_EGR_UG;

    // ==== TIM3 (Red, Green LED) ====
    TIM3->PSC = 83;
    TIM3->ARR = 999;
    TIM3->CCR1 = 0;
    TIM3->CCR2 = 0;
    // CH1 (PB4)
    TIM3->CCMR1 &= ~(7u << 4);
    TIM3->CCMR1 |=  (6u << 4) | (1u << 3);
    TIM3->CCER  |=  TIM_CCER_CC1E | TIM_CCER_CC1P;
    // CH2 (PC7)
    TIM3->CCMR1 &= ~(7u << 12);
    TIM3->CCMR1 |=  (6u << 12) | (1u << 11);
    TIM3->CCER  |=  TIM_CCER_CC2E | TIM_CCER_CC2P;
    TIM3->CR1   |=  TIM_CR1_ARPE | TIM_CR1_CEN;
    TIM3->EGR    =  TIM_EGR_UG;

    // ==== TIM2 (Speaker) ====
    TIM2->PSC = 83; // 1MHz
    TIM2->ARR = 1000 - 1; // 1kHz tone
    TIM2->CCR3 = 0;
    TIM2->CCMR2 &= ~(7u << 4);
    TIM2->CCMR2 |=  (6u << 4) | (1u << 3);
    TIM2->CCER  |=  TIM_CCER_CC3E;
    TIM2->CR1   |=  TIM_CR1_ARPE | TIM_CR1_CEN;
    TIM2->EGR    =  TIM_EGR_UG;
}

void init_analog(void)
{
    // ADC共通設定
    ADC->CCR &= ~(3u << 16);
    ADC->CCR |=  (1u << 16); // PCLK2/4
    ADC1->CR1 &= ~(3u << 24); // 12bit
    ADC1->SMPR2 |= (4u << (0*3)) | (4u << (1*3)); // 84 cycles
    ADC1->SQR1 = 0;
    ADC1->CR2 |= ADC_CR2_ADON;
}

void application_init(EXINF exinf)
{
    syslog(LOG_NOTICE, "INIT START");
    init_rcc();
    init_gpio();
    init_tim();
    init_analog();
}
