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
#include "../../tl_config.h"
#include "tl_button.h"

#ifdef CONFIG_TL_USING_BUTTON_EXAMPLE

#define KEY_PIN 1
#define KEY_PRESS_VALUE 0

static void key_cb(struct tl_button *_button)
{

}

int tl_button_example(void)
{
    /* user app entry */

    return 0;
}

#endif /* CONFIG_TL_USING_BUTTON_EXAMPLE */
