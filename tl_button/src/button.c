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
#include "button.h"

#define _BUTTON_CALL(func, argv) func(argv)
#define BUTTON_CALL(func, argv)       \
    do                                \
    {                                 \
        if ((func) != NULL)        \
            _BUTTON_CALL(func, argv); \
    } while (0)

struct button_manage
{
    uint8_t num;                                 /* 已注册的按键的数目 */
    struct button *button_list[BUTTON_LIST_MAX]; /* 存储按键指针的数组 */
};
static struct button_manage button_manage;

int button_register(struct button *button)
{
    /* 初始化按键对应的 pin 模式 */
    if (button->press_logic_level == 0)
    {
        button_pin_mode_input_pull_up(button->pin);
    }
    else
    {
        button_pin_mode_input_pull_down(button->pin);
    }

    /* 初始化按键结构体 */
    button->cnt = 0;
    button->event = eBUTTON_EVENT_NONE;

    /* 添加按键到管理列表 */
    if (button_manage.num < BUTTON_LIST_MAX)
    {
        button_manage.button_list[button_manage.num++] = button;
    }
    else
    {
        return -1;
    }
    
    return 0;
}

static void button_scan(void *param)
{
    uint8_t i;
    uint16_t cnt_old;

    for (i = 0; i < button_manage.num; i++)
    {
        cnt_old = button_manage.button_list[i]->cnt;

        /* 检测按键的电平状态为按下状态 */
        if (rt_pin_read(button_manage.button_list[i]->pin) == button_manage.button_list[i]->press_logic_level)
        {
            /* 按键扫描的计数值加一 */
            button_manage.button_list[i]->cnt++;

            /* 连续按下的时间达到单击按下事件触发的阈值 */
            if (button_manage.button_list[i]->cnt == BUTTON_DOWN_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_DOWN */
            {
                LOG_D("BUTTON_DOWN");
                button_manage.button_list[i]->event = eBUTTON_EVENT_CLICK_DOWN;
                BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
            /* 连续按下的时间达到长按开始事件触发的阈值 */
            else if (button_manage.button_list[i]->cnt == BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD */
            {
                LOG_D("BUTTON_HOLD");
                button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD;
                BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
            /* 连续按下的时间达到长按周期回调事件触发的阈值 */
            else if (button_manage.button_list[i]->cnt > BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_CYC */
            {
                LOG_D("BUTTON_HOLD_CYC");
                button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD_CYC;
                if (button_manage.button_list[i]->hold_cyc_period && button_manage.button_list[i]->cnt % (button_manage.button_list[i]->hold_cyc_period / BUTTON_SCAN_SPACE_MS) == 0)
                    BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
        }
        /* 检测按键的电平状态为抬起状态 */
        else
        {
            /* 清除按键的计数值 */
            button_manage.button_list[i]->cnt = 0;
            /* 连续按下的时间达到单击结束事件触发的阈值 */
            if (cnt_old >= BUTTON_DOWN_MS / BUTTON_SCAN_SPACE_MS && cnt_old < BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_CLICK_UP */
            {
                LOG_D("BUTTON_CLICK_UP");
                button_manage.button_list[i]->event = eBUTTON_EVENT_CLICK_UP;
                BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
            /* 连续按下的时间达到长按结束事件触发的阈值 */
            else if (cnt_old >= BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_UP */
            {
                LOG_D("BUTTON_HOLD_UP");
                button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD_UP;
                BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
        }
    }
}

int button_start()
{
    button_scan(NULL);

    return 0;
}