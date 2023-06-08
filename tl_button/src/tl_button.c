/**
 * @file button.c
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-03
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "../../tl_config.h"
#include "tl_button.h"

#ifdef CONFIG_TL_USING_BUTTON

#define _BUTTON_CALL(func, argv) func(argv)
#define BUTTON_CALL(func, argv)       \
    do                                \
    {                                 \
        if ((func) != NULL)           \
            _BUTTON_CALL(func, argv); \
    } while (0)

struct tl_button_manage
{
    uint8_t num;                                    /*  */
    struct tl_button *button_list[CONFIG_TL_BUTTON_LIST_MAX]; /*  */
};
static struct tl_button_manage tl_button_manage;

int8_t tl_button_register(struct tl_button *_button,
                          const char *_name,
                          button_callback_t _callback,
                          pin_mode_t _pin_mode,
                          pin_read_t _pin_read,
                          const uint16_t _pin,
                          const uint8_t _press_logic_level,
                          const uint16_t _hold_cyc_period)
{
    // 判断结构体对象是否为空
    if (_button == NULL)
    {
        return -1;
    }

    // 设置对象属性
    _button->id = tl_button_manage.num;
    strncpy(_button->name, _name, 8);
    _button->press_logic_level = _press_logic_level;
    _button->cnt = 0;
    _button->hold_cyc_period = _hold_cyc_period;
    _button->pin = _pin;
    _button->multiple = 0;
    _button->mul_rst_cnt = 0;
    _button->event = eBUTTON_EVENT_NONE;
    _button->cb = _callback;
    _button->pin_mode = _pin_mode;
    _button->pin_read = _pin_read;

    // 检测回调函数
    if (_button->pin_mode == NULL)
    {
        _button->pin_mode = tl_button_pin_mode;
    }
    if (_button->pin_read == NULL)
    {
        _button->pin_read = tl_button_pin_read;
    }
    if (_button->cb == NULL)
    {
        _button->cb = tl_button_callback;
    }

    /* 通过输入逻辑判断将引脚自动配置到对应的模式 */
    if (_button->press_logic_level == 0)
    {
        _button->pin_mode(_button->pin, TL_BUTTON_PIN_PULLUP);
    }
    else
    {
        _button->pin_mode(_button->pin, TL_BUTTON_PIN_PULLDOWN);
    }

    /* 尝试将对象加入管理列表 */
    if (tl_button_manage.num < CONFIG_TL_BUTTON_LIST_MAX)
    {
        tl_button_manage.button_list[tl_button_manage.num++] = _button;
    }
    else
    {
        return -2;
    }

    return 0;
}

static void tl_button_scan(void *param)
{
    uint8_t i, logic_level;
    uint16_t cnt_old;

    for (i = 0; i < tl_button_manage.num; i++)
    {
        cnt_old = tl_button_manage.button_list[i]->cnt;

        if (tl_button_manage.button_list[i]->pin_read == NULL)
        {
            logic_level = tl_button_pin_read(tl_button_manage.button_list[i]->pin);
        }
        else
        {
            logic_level = tl_button_manage.button_list[i]->pin_read(tl_button_manage.button_list[i]->pin);
        }

        /* 判断按键的引脚电平 */
        if (logic_level == tl_button_manage.button_list[i]->press_logic_level)
        {
            /* 按下计时 */
            tl_button_manage.button_list[i]->cnt++;
            tl_button_manage.button_list[i]->mul_rst_cnt = 0;

            /* 计时判断与回调触发 */
            if (tl_button_manage.button_list[i]->cnt == CONFIG_TL_BUTTON_DOWN_MS / CONFIG_TL_BUTTON_SCAN_SPACE_MS) /* BUTTON_DOWN */
            {
                tl_button_manage.button_list[i]->event = eBUTTON_EVENT_CLICK_DOWN;
                BUTTON_CALL(tl_button_manage.button_list[i]->cb, tl_button_manage.button_list[i]);
            }
            else if (tl_button_manage.button_list[i]->cnt == CONFIG_TL_BUTTON_HOLD_MS / CONFIG_TL_BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD */
            {
                tl_button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD;
                BUTTON_CALL(tl_button_manage.button_list[i]->cb, tl_button_manage.button_list[i]);
            }
            else if (tl_button_manage.button_list[i]->cnt > CONFIG_TL_BUTTON_HOLD_MS / CONFIG_TL_BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_CYC */
            {
                tl_button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD_CYC;
                if (tl_button_manage.button_list[i]->hold_cyc_period && tl_button_manage.button_list[i]->cnt % (tl_button_manage.button_list[i]->hold_cyc_period / CONFIG_TL_BUTTON_SCAN_SPACE_MS) == 0)
                    BUTTON_CALL(tl_button_manage.button_list[i]->cb, tl_button_manage.button_list[i]);
            }
        }
        else
        {
            /* 清零计时 */
            tl_button_manage.button_list[i]->cnt = 0;
            tl_button_manage.button_list[i]->mul_rst_cnt++;
            /* 判断计时备份值与回调触发 */
            if (cnt_old >= CONFIG_TL_BUTTON_DOWN_MS / CONFIG_TL_BUTTON_SCAN_SPACE_MS && cnt_old < CONFIG_TL_BUTTON_HOLD_MS / CONFIG_TL_BUTTON_SCAN_SPACE_MS) /* BUTTON_CLICK_UP */
            {
                tl_button_manage.button_list[i]->multiple++;
                if (tl_button_manage.button_list[i]->multiple <= 1)
                {
                    tl_button_manage.button_list[i]->event = eBUTTON_EVENT_CLICK_UP;
                    BUTTON_CALL(tl_button_manage.button_list[i]->cb, tl_button_manage.button_list[i]);
                }
                else
                {
                    tl_button_manage.button_list[i]->event = eBUTTON_EVENT_MULTIPLE;
                    BUTTON_CALL(tl_button_manage.button_list[i]->cb, tl_button_manage.button_list[i]);
                }
            }
            else if (cnt_old >= CONFIG_TL_BUTTON_HOLD_MS / CONFIG_TL_BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_UP */
            {
                tl_button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD_UP;
                BUTTON_CALL(tl_button_manage.button_list[i]->cb, tl_button_manage.button_list[i]);
            }
            /* 定时清零连击次数 */
            if (tl_button_manage.button_list[i]->mul_rst_cnt >= CONFIG_TL_BUTTON_MULTIPLE_RESET_MS)
            {
                tl_button_manage.button_list[i]->mul_rst_cnt = 0;
                tl_button_manage.button_list[i]->multiple = 0;
            }
        }
    }
}

int8_t tl_button_process(const uint32_t _period, const uint32_t _tick)
{
    static uint32_t tick, cnt;

    if (tick != _tick)
    {
        tick = _tick;
        cnt++;
    }

    if (cnt >= _period)
    {
        cnt = 0;

        tl_button_scan(NULL);
    }

    return 0;
}

#ifdef CONFIG_TL_USING_TIMER
static struct tl_timer timer_btn;
int tl_button_start(const uint32_t _period)
{
    tl_timer_register(&timer_btn, "tim btn", tl_button_scan, NULL, _period, TL_TIMER_FLAG_PERIODIC);

    return 0;
}
#endif /* CONFIG_TL_USING_TIMER */

#endif /* CONFIG_TL_USING_BUTTON */
