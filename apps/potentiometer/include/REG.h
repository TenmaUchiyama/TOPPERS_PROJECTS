#ifndef REG_H
#define REG_H

#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))  // GPIOクロック制御

#define RCC_AHB1ENR     (*(volatile uint32_t *)(0x40023830))
#define RCC_APB2ENR     (*(volatile uint32_t *)(0x40023844))
#define GPIOA_MODER     (*(volatile uint32_t *)(0x40020000))
#define ADC1_CR2        (*(volatile uint32_t *)(0x40012008))
#define ADC1_SQR3       (*(volatile uint32_t *)(0x40012034))
#define ADC1_SR         (*(volatile uint32_t *)(0x40012000))
#define ADC1_DR         (*(volatile uint32_t *)(0x4001204C))

#define ADC_CR2_ADON    (1 << 0)
#define ADC_CR2_SWSTART (1 << 30)
#define ADC_SR_EOC      (1 << 1)
#endif
