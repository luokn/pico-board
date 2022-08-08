/*
 * @Data  : 2022/08/06
 * @File  : main.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include <stdio.h>

#include "pico/multicore.h"
#include "pico_board.h"
#include "tusb.h"
#include "usb_descriptors.h"

int main() {
    pico_board_init(); /* Init board. */
    printf("\x1b[1;32m[USB]\x1b[0m tusb_init()\n");

    for (;;) {
        pico_board_task();
    }

    return 0;
}
