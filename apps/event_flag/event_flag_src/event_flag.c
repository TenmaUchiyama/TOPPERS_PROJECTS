#include <kernel.h>
#include <t_syslog.h>
#include "REG.h"
#include "event_flag.h"
#include "kernel_cfg.h"


#define SW_FLAG (1<<0)
#define TIMER_FLAG (1<<1)


void timer_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "[TIMER_TASK] TIMER TASK START");


    while(1)
    {   


        dly_tsk(2000000);
        set_flg(FLG_A, TIMER_FLAG);
        syslog(LOG_NOTICE, "[TIMER_TASK] SENT FLAG");

    }
    ext_tsk();
}

void led_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "[LED_TASK]  LED TASK START");

    while(1)
    {
        FLGPTN acutual_pattern;
        wai_flg(FLG_A, SW_FLAG | TIMER_FLAG, TWF_ORW, &acutual_pattern);

        
        syslog(LOG_NOTICE, "[LED_TASK]  EVENT FLAG RECEIVED: 0x%08X", acutual_pattern);
        if(acutual_pattern & SW_FLAG)
        {
            syslog(LOG_NOTICE, "[LED_TASK] BUTTON RECEIVED");
            GPIOA_ODR ^= (1 << 9); // LEDをトグル
        }

        if(acutual_pattern & TIMER_FLAG)
        {
            syslog(LOG_NOTICE, "[LED_TASK] TIMER UP");
        }

        clr_flg(FLG_A, 0);
        // dly_tsk(10000); // ← この行を削除またはコメントアウトする
    }
    ext_tsk();
}

void sw_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "[SW_TASK]  USER BTN TASK START");

    

    uint8_t prev = 0;  // ボタン離された状態

    while (1)
    {
        // ④ PC13の状態を読む
        uint8_t curr = (GPIOB_IDR & (1 << 5)) ? 1 : 0;

        // ⑤ 押された瞬間だけログを出す
        if (prev == 1 && curr == 0)
        {
            syslog(LOG_NOTICE, "[SW_TASK] USER BUTTON PRESSED");
            set_flg(FLG_A, SW_FLAG);
        }

        prev = curr;

        dly_tsk(10000); // 約10ms待機
    }

    ext_tsk();
}



extern void init_gpio_task(EXINF exinf)
{

    syslog(LOG_NOTICE, "INITIALIZING GPIO");


    
   // Aを有効化
   RCC_AHB1ENR |= (1 << 0); 
   RCC_AHB1ENR |= (1 << 1); 

   //Aを書き込み用にする
   GPIOA_MODER &= ~(0b11 << (9 * 2)); 
   GPIOA_MODER |= (0b01 << (9*2)); 
   GPIOA_ODR |= (1 << 9);


   GPIOB_MODER &= ~(0b11 << (5 * 2));  
   GPIOB_PUPDR &= ~(0b11 << (5 * 2)); // 一旦クリア
    GPIOB_PUPDR |= (0b01 << (5 * 2));  // プルアップ(01)を設定



    act_tsk(LED_TASK); 
    act_tsk(SW_TASK); 
    act_tsk(TIMER_TASK);

    syslog(LOG_NOTICE, "WAKING UP TASKS"); 



}