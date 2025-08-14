#ifndef REG_H
#define REG_H


// ==== LED類 ====
#define BLUE_LED_PORT     GPIOA
#define BLUE_LED_PIN      9    // D8 = PA9

#define GREEN_LED_PORT    GPIOC
#define GREEN_LED_PIN     7    // D9 = PC7

#define RED_LED_PORT      GPIOB
#define RED_LED_PIN       4    // D5 = PB4

// ==== スピーカー ====
#define SPEAKER_PORT      GPIOB
#define SPEAKER_PIN       10   // D6 = PB10

// ==== アナログ入力 ====
#define POT1_PORT         GPIOA
#define POT1_PIN          0    // A0 = PA0

#define POT2_PORT         GPIOA
#define POT2_PIN          1    // A1 = PA1

// ==== ボタン ====
#define RIGHT_BTN_PORT    GPIOC
#define RIGHT_BTN_PIN     0    // A5 = PC0

#define UP_BTN_PORT       GPIOA
#define UP_BTN_PIN        4    // A2 = PA4

#define CENTER_BTN_PORT   GPIOB
#define CENTER_BTN_PIN    5    // D4 = PB5

#define LEFT_BTN_PORT     GPIOC
#define LEFT_BTN_PIN      1    // A4 = PC1

#define DOWN_BTN_PORT     GPIOB
#define DOWN_BTN_PIN      0    // A3 = PB0

// ==== LCD (SPI接続) ====
#define LCD_CS_PORT       GPIOB
#define LCD_CS_PIN        6    // D10 = PB6

#define LCD_A0_PORT       GPIOA
#define LCD_A0_PIN        8    // D7 = PA8

#define LCD_SCK_PORT      GPIOA
#define LCD_SCK_PIN       5    // D13 = PA5

#define LCD_RESET_PORT    GPIOA
#define LCD_RESET_PIN     6    // D12(MISO) = PA6

#define LCD_MOSI_PORT     GPIOA
#define LCD_MOSI_PIN      7    // D11(MOSI) = PA7


#endif