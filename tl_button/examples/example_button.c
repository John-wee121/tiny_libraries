/**
 * @file example_button.c
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-03
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <../../tl_config.h>
#include <tl_button.h>

#ifdef CONFIG_TL_USING_BUTTON_EXAMPLE

#define KEY_PIN 1
#define KEY_PRESS_VALUE 0

static void key_cb(struct button *button)
{
    switch (button->event)
    {
    case eBUTTON_EVENT_CLICK_UP:
        rt_kprintf("This is click up callback!\n");
        break;
    case eBUTTON_EVENT_HOLD_CYC:
        rt_kprintf("This is hold cyc callback!\n");
        break;
    default:;
    }
}

int tl_button_example(void)
{
    /* user app entry */
    static struct button key = {0};

    key.press_logic_level = KEY_PRESS_VALUE;
    key.hold_cyc_period = 100;
    key.cb = (button_callback)key_cb;
    key.pin = KEY_PIN;

    button_register(&key);
    button_start();

    return 0;
}

#endif /* CONFIG_TL_USING_BUTTON_EXAMPLE */
