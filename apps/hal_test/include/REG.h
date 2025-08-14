#ifndef REG_H
#define REG_H

#include <stdint.h>

// RCC
#define RCC_BASE         0x40023800UL
#define RCC_AHB1ENR      (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB2ENR      (*(volatile uint32_t*)(RCC_BASE + 0x44))

// GPIO
#define GPIOA_BASE       0x40020000UL
#define GPIOB_BASE       0x40020400UL

#define GPIOA_MODER      (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER     (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR    (*(volatile uint32_t*)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR      (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))
#define GPIOA_ODR        (*(volatile uint32_t*)(GPIOA_BASE + 0x14))

#define GPIOB_MODER      (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOB_PUPDR      (*(volatile uint32_t*)(GPIOB_BASE + 0x0C))

// SYSCFG
#define SYSCFG_BASE      0x40013800UL
#define SYSCFG_EXTICR    ((volatile uint32_t*)(SYSCFG_BASE + 0x08))

// EXTI
#define EXTI_BASE        0x40013C00UL
#define EXTI_IMR         (*(volatile uint32_t*)(EXTI_BASE + 0x00))
#define EXTI_EMR         (*(volatile uint32_t*)(EXTI_BASE + 0x04))
#define EXTI_RTSR        (*(volatile uint32_t*)(EXTI_BASE + 0x08))
#define EXTI_FTSR        (*(volatile uint32_t*)(EXTI_BASE + 0x0C))
#define EXTI_PR          (*(volatile uint32_t*)(EXTI_BASE + 0x14))

// NVIC
#define NVIC_ISER1       (*(volatile uint32_t*)0xE000E104)

#endif
