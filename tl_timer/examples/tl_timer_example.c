/**
 * @file tl_timer_example.c
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-05
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <../../tl_config.h>
#include <tl_timer.h>

#ifdef CONFIG_TL_USING_TIMER_EXAMPLE
struct tl_timer timer0;

void timer0_cb(void *_parameter)
{
}

int tl_timer_test(void)
{
    uint32_t tick;

    tl_timer_register(&timer0, "timer0", timer0_cb, &tick, 1000, TL_TIMER_FLAG_PERIODIC);

    while (1)
    {
        // 放置硬件定时器中，并设置好计时周期和硬件定时器的节拍
        tl_timer_process(1, tick);
    }

    return 0;
}
#endif
