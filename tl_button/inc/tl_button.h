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

#define BUTTON_DOWN_MS 50
#define BUTTON_HOLD_MS 700

#define BUTTON_SCAN_SPACE_MS 20
#define BUTTON_LIST_MAX 10

typedef void (*button_callback)(void *);

enum button_event
{
    eBUTTON_EVENT_CLICK_DOWN, /* 按键单击按下事件 */
    eBUTTON_EVENT_CLICK_UP,   /* 按键单击结束事件 */
    eBUTTON_EVENT_HOLD,       /* 按键长按开始事件 */
    eBUTTON_EVENT_HOLD_CYC,   /* 按键长按周期性触发事件 */
    eBUTTON_EVENT_HOLD_UP,    /* 按键长按结束事件 */
    eBUTTON_EVENT_NONE,       /* 无按键事件 */
};

struct button
{
    uint8_t press_logic_level; /* 按键按下时的电平 */
    uint16_t cnt;              /* 连续扫描到按下状态的次数 */
    uint16_t hold_cyc_period;  /* 长按周期回调的周期 */
    uint16_t pin;              /* 按键对应的 pin 编号 */

    enum button_event event; /* 按键的触发的事件 */

    button_callback cb; /* 按键触发事件回调函数 */
};

int button_register(struct button *button);
int button_start(void);

// port api
void button_pin_mode_input_pull_up(const uint16_t _pin);
void button_pin_mode_input_pull_down(const uint16_t _pin);
void button_timer_handler(void);

#endif /* CONFIG_TL_USING_BUTTON */

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H */
