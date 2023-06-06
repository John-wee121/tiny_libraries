/**
 * @file hello.c
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

#ifdef CONFIG_USING_TL_TIMER

struct tl_timer_manage
{
    uint8_t number;
    struct tl_timer *timer_list[eTL_TIMER_MAX];
};
struct tl_timer_manage tl_timer_manage = {
    .number = 0,
};

void tl_timer_enable(struct tl_timer *_timer)
{
    _timer->flag |= TL_TIMER_FLAG_EN;
}

void tl_timer_disable(struct tl_timer *_timer)
{
    _timer->flag &= ~TL_TIMER_FLAG_EN;
}

int8_t tl_timer_is_enable(struct tl_timer *_timer)
{
    return (_timer->flag & TL_TIMER_FLAG_EN);
}

int8_t tl_timer_register(struct tl_timer *_timer,
                         const char *_name,
                         void (*_timeout)(void *parameter),
                         void *_parameter,
                         uint32_t _time,
                         uint8_t _flag)
{
    if ((_timer == NULL) || (tl_timer_manage.number >= eTL_TIMER_MAX))
    {
        return -1;
    }

    _timer->id = tl_timer_manage.number;
    strncpy(_timer->name, _name, 8);
    _timer->cb = _timeout;
    _timer->parameter = _parameter;
    _timer->time = _time;
    _timer->flag = _flag | TL_TIMER_FLAG_EN;

    tl_timer_manage.timer_list[tl_timer_manage.number] = _timer;
    tl_timer_manage.number += 1;

    return 0;
}

static void tl_timer_task(void)
{
    for (uint8_t i = 0; i < tl_timer_manage.number; i++)
    {
        if (tl_timer_is_enable(tl_timer_manage.timer_list[i]))
        {
            if (tl_timer_manage.timer_list[i]->flag & TL_TIMER_FLAG_ONE_SHOT)
            {
                tl_timer_manage.timer_list[i]->cnt++;
                if (tl_timer_manage.timer_list[i]->cnt >= tl_timer_manage.timer_list[i]->time)
                {
                    tl_timer_manage.timer_list[i]->cnt = 0;
                    tl_timer_disable(tl_timer_manage.timer_list[i]);
                    tl_timer_manage.timer_list[i]->cb(tl_timer_manage.timer_list[i]->parameter);
                }
            }
            else if (tl_timer_manage.timer_list[i]->flag & TL_TIMER_FLAG_PERIODIC)
            {
                tl_timer_manage.timer_list[i]->cnt++;
                if (tl_timer_manage.timer_list[i]->cnt >= tl_timer_manage.timer_list[i]->time)
                {
                    tl_timer_manage.timer_list[i]->cnt = 0;
                    tl_timer_manage.timer_list[i]->cb(tl_timer_manage.timer_list[i]->parameter);
                }
            }
        }
    }
}

int8_t tl_timer_process(const uint32_t _period, const uint32_t _tick)
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

        tl_timer_task();
    }

    return 0;
}

#endif /* CONFIG_USING_TL_TIMER */
