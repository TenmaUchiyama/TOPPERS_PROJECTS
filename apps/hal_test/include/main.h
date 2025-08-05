#ifndef MAIN_H
#define MAIN_H

#include <kernel.h>

void init_gpio(EXINF exinf);
void ISR_EXTI9_5(void);  // 割込みハンドラ

#endif
