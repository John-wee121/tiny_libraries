/**
 * @file tl_timer.h
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-05
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef TL_TIMER_H
#define TL_TIMER_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef CONFIG_USING_TL_TIMER

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define TL_TIMER_FLAG_EN        0x01
#define TL_TIMER_FLAG_ONE_SHOT  0x02
#define TL_TIMER_FLAG_PERIODIC  0x04

    enum tl_timer_index
    {
        eTL_TIMER_0 = 0,
        eTL_TIMER_1,

        eTL_TIMER_MAX,
    };

    struct tl_timer
    {
        uint8_t id; // 瀹氭椂鍣↖D
        char name[8]; // 瀹氭椂鍣ㄥ悕锟�?

        uint32_t cnt;  // 璁℃暟锟�?
        uint32_t time; // 瀹氭椂鍣ㄨ秴鏃跺懆锟�?
        uint8_t flag;  // 瀹氭椂鍣ㄦ爣锟�?

        void (*cb)(void *parameter);
        void *parameter;
    };

    void tl_timer_enable(struct tl_timer *_timer);
    void tl_timer_disable(struct tl_timer *_timer);
    int8_t tl_timer_is_enable(struct tl_timer *_timer);
    int8_t tl_timer_register(struct tl_timer *_timer,
                             const char *_name,
                             void (*_timeout)(void *parameter),
                             void *_parameter,
                             uint32_t _time,
                             uint8_t _flag);
    int8_t tl_timer_process(const uint32_t _period, const uint32_t _tick);

#endif /* CONFIG_USING_TL_TIMER */

#ifdef __cplusplus
}
#endif

#endif /* TL_TIMER_H */
