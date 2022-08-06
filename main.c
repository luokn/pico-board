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

void setup();
void loop();

int main() {
    for (setup();;) {
        loop();
    }

    return 0;
}

void setup() {
    /*
     * Init board.
     */

    board_init();

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
     * Blink LED.
     */

    led_blink_task();

    /*
     * Report keyboard.
     */

    hid_report_task();
}
