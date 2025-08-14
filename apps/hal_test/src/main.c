#include <kernel.h>
#include <t_syslog.h>
#include "main.h"
#include "kernel_cfg.h"

#include "stm32f4xx_nucleo.h"

void init_gpio(EXINF exinf)
{
    syslog(LOG_NOTICE, "INIT_GPIO START");

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    // LED出力（PA9）
    GPIO_InitTypeDef led = {0};
    led.Pin = GPIO_PIN_9;
    led.Mode = GPIO_MODE_OUTPUT_PP;
    led.Pull = GPIO_NOPULL;
    led.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &led);

    // ボタン入力（PB5）をEXTI割込みに設定
    GPIO_InitTypeDef btn = {0};
    btn.Pin = GPIO_PIN_5;
    btn.Mode = GPIO_MODE_IT_FALLING;  // フォールエッジで割込み
    btn.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &btn);

    // NVIC（EXTI9_5_IRQn = 23）有効化 ← カーネルがCFG_INTで許可するので不要
    // HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

// STM32 HALの割込みハンドラに渡すだけ
void ISR_EXTI9_5(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}

// ユーザーコールバック（割込み発生時にHALから呼ばれる）
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_5)
    {
        syslog(LOG_NOTICE, "PB5 Interrupt Detected");
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);  // LEDトグル
    }
}
