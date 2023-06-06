/**
 * @file tiny_libraries_config.c
 * @author JohnWay (1973372075@qq.com)
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023 JohnWay
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int choose;

    /* code */
    while (1)
    {
        printf("\n\n");
        printf("Tiny Libraries Config\n");
        printf("[0] Exit config\n");
        printf("[1] Enter config\n");
        printf("[2] Up to config\n");
        printf("[3] clear screen\n");
        printf("input:");
        scanf("%d", &choose);
        getchar();
        printf("output:%d\n", choose);
        switch (choose)
        {
        case 0:
            goto __exit;
            break;
        case 1:
            system("menuconfig");
            break;
        case 2:
            system("mingw32-make");
            break;
        case 3:
            system("cls");
            break;
        }
    }

__exit:
    return 0;
}
