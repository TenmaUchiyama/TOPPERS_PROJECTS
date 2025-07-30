#include <kernel.h>
#include <t_syslog.h>
#include "REG.h"
#include "simple_btn.h"


void sw_task(EXINF exinf)
{
    syslog(LOG_NOTICE, "USER BTN TASK START");

    // ① GPIOC クロック有効化
    RCC_AHB1ENR |= (1 << 2);  // GPIOC = bit 2

    // ② PC13 を入力モードに設定（MODER13 = 00）
    GPIOC_MODER &= ~(0b11 << (13 * 2));  // 入力モード

    // ③ PUPDR は基本不要（Nucleoボードは外部プルダウン回路付き）
    GPIOC_PUPDR &= ~(0b11 << (13 * 2));  // プルアップ・プルダウン無効

    uint8_t prev = 1;  // ボタン離された状態

    while (1)
    {
        // ④ PC13の状態を読む
        uint8_t curr = (GPIOC_IDR & (1 << 13)) ? 1 : 0;

        // ⑤ 押された瞬間だけログを出す
        if (prev == 1 && curr == 0)
        {
            syslog(LOG_NOTICE, "USER BUTTON PRESSED");
        }

        prev = curr;

        dly_tsk(10000); // 約10ms待機
    }

    ext_tsk();
}
