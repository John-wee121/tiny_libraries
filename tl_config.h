/**
 * @file tl_config.h
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-05
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef TL_CONFIG_H
#define TL_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "autoconfig.h"

#ifdef CONFIG_TL_USING_BUTTON
#include "tl_button.h"
#endif

#ifdef CONFIG_TL_USING_TIMER
#include "tl_timer.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* TL_CONFIG_H */
