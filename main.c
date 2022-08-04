/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blink.h"
#include "bsp/board.h"
#include "hardware/irq.h"
#include "hardware/uart.h"
#include "hid_report.h"
#include "pico/multicore.h"
#include "pico/stdio.h"
#include "tusb.h"
#include "usb_descriptors.h"

// void hid_report_task(void);

// const uint8_t key_table[][2] = {HID_ASCII_TO_KEYCODE};

int main() {
    board_init();

    tusb_init();
    printf("\x1b[1;32m[USB]\x1b[0m tusb_init()\n");

    for (;;) {
        tud_task(); /* tinyusb device task */
        led_blink_task();
        hid_report_task();
    }

    return 0;
}

// int main(void) {
//     board_init();
//     tusb_init();

//     for (;;) {
//         tud_task();  // tinyusb device task
//         led_blink_task();
//         // hid_report_task();

//         char chr;
//         scanf("%c", &chr);

//         uint8_t modifier   = 0;
//         uint8_t keycode[6] = {0};

//         if (key_table[chr][0]) {
//             modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
//         }
//         keycode[0] = key_table[chr][1];
//         // tud_hid_keyboard_report(report_id, modifier, keycode);

//         tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycode);
//     }

//     return 0;
// }
