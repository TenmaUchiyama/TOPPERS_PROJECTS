#ifndef MBED_SHIELD_H
#define MBED_SHIELD_H




void set_rgb(uint8_t r_percent, uint8_t g_percent, uint8_t b_percent);
void read_pot_A(void);
void read_pot_B(void);

void speaker_set_freq(uint32_t hz);
void speaker_on(void);
void speaker_off(void);

void lcd_select(void);
void lcd_deselect(void);
void lcd_cmd_mode(void);
void lcd_data_mode(void);
void lcd_reset(void);

uint8_t read_button_right(void);
uint8_t read_button_up(void);
uint8_t read_button_center(void);
uint8_t read_button_left(void);
uint8_t read_button_down(void);

uint8_t read_all_buttons(void); // ビットマスク形式
void buttons_enable_interrupts(void);


float pot_to_percent(uint16_t adc_val);
float pot_to_voltage(uint16_t adc_val);

void gpio_set(GPIO_TypeDef* port, uint32_t pin);
void gpio_reset(GPIO_TypeDef* port, uint32_t pin);
void gpio_toggle(GPIO_TypeDef* port, uint32_t pin);


void pwm_set_duty(TIM_TypeDef* tim, uint8_t channel, uint8_t percent);



#endif