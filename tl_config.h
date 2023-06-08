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
#include <stdint.h>
#include <math.h>

// 将两个U8合并为一个
#define TL_U8_TWO_IN_ONE_HIGH(_high, _low) (((_high) & 0xF0) | (((_low) >> 4) & 0x0F))
#define TL_U8_TWO_IN_ONE_LOW(_high, _low) ((((_high) << 4) & 0xF0) | ((_low) & 0x0F))
#define TL_U8_TWO_IN_ONE(_high, _low, _ops) ({(_ops) == 0 ? TL_U8_TWO_IN_ONE_LOW(_high, _low) : TL_U8_TWO_IN_ONE_HIGH(_high, _low);})

// 设置数值操作函数选择
#define TL_FN_RANGE 0
#define TL_FN_LIMIT 1
// 设置数值加减选择
#define TL_OPS_SUB 0
#define TL_OPS_ADD 1
// 数值操作函数-循环加减
#define TL_VALUE_ADD_RANGE(_min, _max, _num, _val) (((_val) < (_max)) ? (((_val) + (_num)) > (_max) ? (_max) : ((_val) += (_num))) : ((_val) = (_min)))
#define TL_VALUE_SUB_RANGE(_min, _max, _num, _val) (((_val) > (_min)) ? (((_val) - (_num)) < (_min) ? (_min) : ((_val) -= (_num))) : ((_val) = (_max)))
#define TL_SET_VALUE_RANGE(_min, _max, _ops, _num, _val) ({(_ops == 0) ? TL_VALUE_SUB_RANGE(_min, _max, _num, _val) : TL_VALUE_ADD_RANGE(_min, _max, _num, _val);})
// 数值操作函数-停留极限
#define TL_VALUE_ADD_LIMIT(_min, _max, _num, _val) (((_val) < (_max)) ? (((_val) + (_num)) > (_max) ? (_max) : ((_val) += (_num))) : ((_val) = (_max)))
#define TL_VALUE_SUB_LIMIT(_min, _max, _num, _val) (((_val) > (_min)) ? (((_val) - (_num)) < (_min) ? (_min) : ((_val) -= (_num))) : ((_val) = (_min)))
#define TL_SET_VALUE_LIMIT(_min, _max, _ops, _num, _val) ({(_ops == 0) ? TL_VALUE_SUB_LIMIT(_min, _max, _num, _val) : TL_VALUE_ADD_LIMIT(_min, _max, _num, _val);})
/**
 * @brief 数值操作函数
 * @param _min 最小值
 * @param _max 最大值
 * @param _fn 功能选择
 * @param _ops 操作选择
 * @param _num 加减数值
 * @param _val 改变的目标值
 * @return 改变后的目标值
 */
inline static int32_t tl_set_value(const int32_t _min, const int32_t _max, const uint8_t _fn, const uint8_t _ops, const int32_t _num, int32_t _val)
{
    int32_t tmp_num = 1, result = 0;

    tmp_num = _num;

    if (_fn)
    {
        result = TL_SET_VALUE_LIMIT(_min, _max, _ops, tmp_num, _val);
    }
    else
    {
        result = TL_SET_VALUE_RANGE(_min, _max, _ops, tmp_num, _val);
    }

    return result;
}

/**
 * @brief
 *
 * @param _min
 * @param _max
 * @param _val
 * @return int32_t
 */
inline static int32_t tl_range_check(const int32_t _min, const int32_t _max, int32_t _val)
{
    if (_val < _min)
    {
        _val = _min;
    }
    else if (_val > _max)
    {
        _val = _max;
    }

    return _val;
}

/**
 * @brief
 * Gamma校正：
 * 原理: R=255x(R/255)^(1/Gamma), G=255x(G/255)^(1/Gamma), B=255x(B/255)^(1/Gamma). 当Gamma等于0.5时, 就是暗黑效果.
 * @param _data
 * @param _gamma [0:1] (0.4 = 1 / 2.5)
 * @return int32_t
 */
inline static int32_t tl_gamma_16bit(int32_t _data, const double _gamma)
{
    _data = pow((double)_data / 255.0, 1.0 / _gamma) * 65535;
    return tl_range_check(0, 65535, _data);
}

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
