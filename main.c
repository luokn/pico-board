/*
 * @Data  : 2022/08/06
 * @File  : main.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include <stdio.h>

#include "pico_board.h"

int main() {
    /* Init board. */
    pico_board_init();

    /* Do board task. */
    while (1) {
        pico_board_task();
    }

    return 0;
}
