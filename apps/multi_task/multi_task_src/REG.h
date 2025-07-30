#ifndef REG_H 
#define REG_H







#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (*(volatile uint32_t* )(RCC_BASE + 0x00) )

#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

#define GPIOC_BASE 0x40020800
#define GPIOC_MODER (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR    (*(volatile uint32_t *)(GPIOC_BASE + 0x0C)) 
#define GPIOC_IDR   (*(volatile uint32_t *)(GPIOC_BASE + 0x10))



#endif