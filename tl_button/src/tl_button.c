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
#include <../../tl_config.h>
#include <tl_button.h>

#ifdef CONFIG_TL_USING_BUTTON

#define _BUTTON_CALL(func, argv) func(argv)
#define BUTTON_CALL(func, argv)       \
    do                                \
    {                                 \
        if ((func) != NULL)        \
            _BUTTON_CALL(func, argv); \
    } while (0)

struct button_manage
{
    uint8_t num;                                 /* 宸叉敞鍐岀殑鎸夐敭鐨勬暟鐩? */
    struct button *button_list[BUTTON_LIST_MAX]; /* 瀛樺偍鎸夐敭鎸囬拡鐨勬暟缁? */
};
static struct button_manage button_manage;

int button_register(struct button *button)
{
    /* 鍒濆鍖栨寜閿搴旂殑 pin 妯″紡 */
    if (button->press_logic_level == 0)
    {
        button_pin_mode_input_pull_up(button->pin);
    }
    else
    {
        button_pin_mode_input_pull_down(button->pin);
    }

    /* 鍒濆鍖栨寜閿粨鏋勪綋 */
    button->cnt = 0;
    button->event = eBUTTON_EVENT_NONE;

    /* 娣诲姞鎸夐敭鍒扮鐞嗗垪琛? */
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

        /* 妫?娴嬫寜閿殑鐢靛钩鐘舵?佷负鎸変笅鐘舵?? */
        if (rt_pin_read(button_manage.button_list[i]->pin) == button_manage.button_list[i]->press_logic_level)
        {
            /* 鎸夐敭鎵弿鐨勮鏁板?煎姞涓? */
            button_manage.button_list[i]->cnt++;

            /* 杩炵画鎸変笅鐨勬椂闂磋揪鍒板崟鍑绘寜涓嬩簨浠惰Е鍙戠殑闃堝?? */
            if (button_manage.button_list[i]->cnt == BUTTON_DOWN_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_DOWN */
            {
                button_manage.button_list[i]->event = eBUTTON_EVENT_CLICK_DOWN;
                BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
            /* 杩炵画鎸変笅鐨勬椂闂磋揪鍒伴暱鎸夊紑濮嬩簨浠惰Е鍙戠殑闃堝?? */
            else if (button_manage.button_list[i]->cnt == BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD */
            {
                button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD;
                BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
            /* 杩炵画鎸変笅鐨勬椂闂磋揪鍒伴暱鎸夊懆鏈熷洖璋冧簨浠惰Е鍙戠殑闃堝?? */
            else if (button_manage.button_list[i]->cnt > BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_CYC */
            {
                button_manage.button_list[i]->event = eBUTTON_EVENT_HOLD_CYC;
                if (button_manage.button_list[i]->hold_cyc_period && button_manage.button_list[i]->cnt % (button_manage.button_list[i]->hold_cyc_period / BUTTON_SCAN_SPACE_MS) == 0)
                    BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
        }
        /* 妫?娴嬫寜閿殑鐢靛钩鐘舵?佷负鎶捣鐘舵?? */
        else
        {
            /* 娓呴櫎鎸夐敭鐨勮鏁板?? */
            button_manage.button_list[i]->cnt = 0;
            /* 杩炵画鎸変笅鐨勬椂闂磋揪鍒板崟鍑荤粨鏉熶簨浠惰Е鍙戠殑闃堝?? */
            if (cnt_old >= BUTTON_DOWN_MS / BUTTON_SCAN_SPACE_MS && cnt_old < BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_CLICK_UP */
            {
                button_manage.button_list[i]->event = eBUTTON_EVENT_CLICK_UP;
                BUTTON_CALL(button_manage.button_list[i]->cb, button_manage.button_list[i]);
            }
            /* 杩炵画鎸変笅鐨勬椂闂磋揪鍒伴暱鎸夌粨鏉熶簨浠惰Е鍙戠殑闃堝?? */
            else if (cnt_old >= BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_UP */
            {
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

#endif /* CONFIG_TL_USING_BUTTON */
