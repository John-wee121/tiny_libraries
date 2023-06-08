/**
 * @file button.h
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-03
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef CONFIG_TL_USING_BUTTON

#include <stddef.h>
#include <stdint.h>

// 引脚模式
#define TL_BUTTON_PIN_PULLUP 0
#define TL_BUTTON_PIN_PULLDOWN 1

    //
    typedef void (*button_callback_t)(void *);
    typedef void (*pin_mode_t)(const uint16_t _pin, const uint8_t _mode);
    typedef uint8_t (*pin_read_t)(const uint16_t _pin);

    enum tl_button_event
    {
        eBUTTON_EVENT_CLICK_DOWN, /* 按键单击按下事件 */
        eBUTTON_EVENT_CLICK_UP,   /* 按键单击结束事件 */
        eBUTTON_EVENT_HOLD,       /* 按键长按开始事件 */
        eBUTTON_EVENT_HOLD_CYC,   /* 按键长按周期性触发事件 */
        eBUTTON_EVENT_HOLD_UP,    /* 按键长按结束事件 */
        eBUTTON_EVENT_MULTIPLE,   /* 按键连击事件 */
        eBUTTON_EVENT_NONE,       /* 无按键事件 */
    };

    struct tl_button
    {
        uint8_t id;
        char name[8];

        uint8_t press_logic_level; /* 按键按下时的电平 */
        uint16_t cnt;              /* 连续扫描到按下状态的次数 */
        uint16_t hold_cyc_period;  /* 长按周期回调的周期 */
        uint16_t pin;              /* 按键对应的 pin 编号 */
        uint16_t multiple;         /* 按键连击次数 */
        uint16_t mul_rst_cnt;      /* 按键连击次数清零计数 */

        enum tl_button_event event; /* 按键的触发的事件 */

        button_callback_t cb; /* 按键触发事件回调函数 */
        pin_mode_t pin_mode;
        pin_read_t pin_read;
    };

    // api
    int8_t tl_button_register(struct tl_button *_button,
                              const char *_name,
                              button_callback_t _callback,
                              pin_mode_t _pin_mode,
                              pin_read_t _pin_read,
                              const uint16_t _pin,
                              const uint8_t _press_logic_level,
                              const uint16_t _hold_cyc_period);
    int8_t tl_button_process(const uint32_t _period, const uint32_t _tick);
#ifdef CONFIG_TL_USING_TIMER
    int tl_button_start(const uint32_t _period);
#endif /* CONFIG_TL_USING_TIMER */

    // port api
    void tl_button_callback(void *parameter);
    void tl_button_pin_mode(const uint16_t _pin, const uint8_t _mode);
    uint8_t tl_button_pin_read(const uint16_t _pin);

#endif /* CONFIG_TL_USING_BUTTON */

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H */
