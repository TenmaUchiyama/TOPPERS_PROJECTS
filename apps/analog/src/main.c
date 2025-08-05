#include "main.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

ADC_HandleTypeDef hadc1;
osMutexId adcMutexHandle;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
void StickATask(void const * argument);
void StickBTask(void const * argument);

// ADC 初期化（HAL方式）
static void MX_ADC1_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    if (HAL_ADC_Init(&hadc1) != HAL_OK) {
        Error_Handler();
    }

    // 初期化ではチャンネル設定しない
}

// GPIO初期化（PA0/PA1アナログ用）
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// アナログ読み取り（ミューテックス保護）
uint16_t ReadAnalogChannel(uint32_t channel)
{
    uint16_t value = 0;

    osMutexWait(adcMutexHandle, osWaitForever);

    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
        value = HAL_ADC_GetValue(&hadc1);
    }

    HAL_ADC_Stop(&hadc1);
    osMutexRelease(adcMutexHandle);

    return value;
}

// スティックA: PA0 -> ADC_CHANNEL_0
void StickATask(void const * argument)
{
    for (;;) {
        uint16_t val = ReadAnalogChannel(ADC_CHANNEL_0);
        printf("Stick A (PA0): %u\r\n", val);
        osDelay(50); // 50ms
    }
}

// スティックB: PA1 -> ADC_CHANNEL_1
void StickBTask(void const * argument)
{
    for (;;) {
        uint16_t val = ReadAnalogChannel(ADC_CHANNEL_1);
        printf("Stick B (PA1): %u\r\n", val);
        osDelay(50);
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC1_Init();

    osMutexDef(adcMutexHandle);
    adcMutexHandle = osMutexCreate(osMutex(adcMutexHandle));

    osThreadDef(stickA, StickATask, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(stickA), NULL);

    osThreadDef(stickB, StickBTask, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(stickB), NULL);

    osKernelStart();

    while (1) {}
}
