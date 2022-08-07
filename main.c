/*
 * @Data  : 2022/08/06
 * @File  : main.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include <stdio.h>

#include "blink.h"
#include "bsp/board.h"
#include "hid_report.h"
#include "pico/multicore.h"
#include "tusb.h"

void setup() {
    /*
     * Init board.
     */

    board_init();

    static const uint8_t arr[] = {
        [0] = 1,
        [2] = 1,
        [3] = 0,
    };

    printf("[%d, %d, %d, %d]\n", arr[0], arr[1], arr[2], arr[3]);

    /*
     * Init USB.
     */
    tusb_init();
    printf("\x1b[1;32m[USB]\x1b[0m tusb_init()\n");
}

void loop() {
    /*
     *  Process tinyusb endpoint events.
     */

    tud_task();

    /*
     * Report keyboard.
     */

    hid_report_task();
}

int main() {
    setup();

    for (;;) {
        loop();
    }

    return 0;
}
