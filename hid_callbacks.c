/*
 * @Data  : 2022/08/06
 * @File  : hid_callbacks.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include <stdio.h>

#include "blink.h"
#include "bsp/board.h"
#include "hid_report.h"

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len) {
    uint8_t report_id = report[0];

    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_report_complete_cb(): id = %u, report = [ ", report_id);
    for (uint8_t i = 1; i < len; i++) {
        printf("%02x ", report[i]);
    }
    printf("]\n");
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer,
                               uint16_t reqlen) {
    hid_keyboard_report_t report;

    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_get_report_cb(): id = %u, type = %u\n", report_id, report_type);

    if (reqlen < sizeof(report)) return 0;

    uint8_t keycode[6] = {HID_KEY_CAPS_LOCK, 0, 0, 0, 0, 0};
    report.modifier    = 0;
    report.reserved    = 0;
    memcpy(report.keycode, keycode, sizeof(report.keycode));
    memcpy(buffer, &report, sizeof(report));
    return sizeof(report);
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer,
                           uint16_t bufsize) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_set_report_cb(): id = %u, type = %u, buffer = [ ", report_id, report_type);
    for (uint16_t i = 0; i < bufsize; i++) {
        printf("%02x ", buffer[i]);
    }
    printf("]\n");

    // if (report_type == HID_REPORT_TYPE_OUTPUT) {
    //     // Set keyboard LED e.g Capslock, Numlock etc...
    //     if (report_id == REPORT_ID_KEYBOARD) {
    //         // bufsize should be (at least) 1
    //         if (bufsize < 1) return;

    //         uint8_t const kbd_leds = buffer[0];

    //         if (kbd_leds & KEYBOARD_LED_CAPSLOCK) {
    //             // Capslock On: disable blink, turn led on
    //             blink_intv_ms = 0;
    //             board_led_write(true);
    //         } else {
    //             // Caplocks Off: back to normal blink
    //             board_led_write(false);
    //             blink_intv_ms = BLINK_MOUNTED;
    //         }
    //     }
    // }
}

void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_set_protocol_cb(): protocol = %u\n", protocol);
}

bool tud_hid_set_idle_cb(uint8_t instance, uint8_t idle_rate) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_set_idle_cb(): idle_rate = %u\n", idle_rate);
    return true;
}
