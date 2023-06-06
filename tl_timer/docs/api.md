# tl_timer API

## 软定时器使能

`void tl_timer_enable(struct tl_timer *_timer)`

| 参数              | 描述                                |
|:------------------|:------------------------------------|
|`_timer`           | 定时器结构体指针                     |

## 软定时器失能

`void tl_timer_disable(struct tl_timer *_timer)`

| 参数              | 描述                                |
|:------------------|:------------------------------------|
|`_timer`           | 定时器结构体指针                     |

## 判断软定时器是否使能

`uint8_t tl_timer_is_enable(struct tl_timer *_timer)`

| 参数              | 描述                                |
|:------------------|:------------------------------------|
|`_timer`           | 定时器结构体指针                     |
| **返回**          | **描述**                            |
| 0                 | 定时器失能                           |
| 1                 | 定时器使能                           |

## 软定时器注册函数

`int8_t tl_timer_register(struct tl_timer *_timer, const char *_name, void (*_timeout)(void *parameter), void *_parameter, uint32_t _time, uint8_t _flag);`

| 参数              | 描述                                |
|:------------------|:------------------------------------|
|`_timer`           | 定时器结构体指针                     |
|`_name_`           | 定时器名字                     |
|`_timeout`         | 定时器超时回调函数                     |
|`_parameter`       | 定时器超时回调函数的参数                     |
|`_time`            | 定时器计时周期                     |
|`_flag`            | 定时器标记                     |
| **返回**          | **描述**                            |
| 0                 | 定时器注册成功                           |
| -1                | 定时器注册失败                           |

## 软定时器进程

`int8_t tl_timer_process(const uint32_t _period, const uint32_t _tick)`

| 参数              | 描述                                |
|:------------------|:------------------------------------|
|`_period`          | 定时器计时周期                     |
|`_tick`            | 定时器计数节拍                     |
| **返回**          | **描述**                            |
| 0                 | 定时器运行                           |

## [示例](../examples/tl_timer_example.c)

```c
/**
 * @file tl_timer_example.c
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-05
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <../../tl_config.h>
#include <tl_timer.h>

#ifdef CONFIG_TL_USING_TIMER_EXAMPLE
struct tl_timer timer0;

void timer0_cb(void *_parameter)
{
}

int tl_timer_test(void)
{
    uint32_t tick;

    tl_timer_register(&timer0, "timer0", timer0_cb, &tick, 1000, TL_TIMER_FLAG_PERIODIC);

    while (1)
    {
        // 放置硬件定时器中，并设置好计时周期和硬件定时器的节拍
        tl_timer_process(1, tick);
    }

    return 0;
}
#endif
```
