/**
 * @file button_port.c
 * @author JohnWay (1973372075@qq.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-04
 * 
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 * 
 */
#include "../../tl_config.h"
#include "tl_button.h"

#ifdef CONFIG_TL_USING_BUTTON

void tl_button_callback(void *parameter)
{

}

void tl_button_pin_mode(const uint16_t _pin, const uint8_t _mode)
{

}

uint8_t tl_button_pin_read(const uint16_t _pin)
{

    return 0;
}

#endif /* CONFIG_TL_USING_BUTTON */
