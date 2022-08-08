/*
 * @Data  : 2022/08/06
 * @File  : hid_callbacks.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include <stdio.h>

#include "bsp/board.h"
#include "usb_descriptors.h"

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len) {
    uint8_t report_id = report[0];

    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_report_complete_cb(): id = %u, report = [ ", report_id);
    for (uint8_t i = 1; i < len; i++) {
        printf("%02x ", report[i]);
    }
    printf("]\n");
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buf,
                               uint16_t req_len) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_get_report_cb(): id = %u, type = %u\n", report_id, report_type);

    hid_keyboard_report_t report = {
        .modifier = 0,
        .reserved = 0,
        .keycode  = {HID_KEY_CAPS_LOCK, 0, 0, 0, 0, 0},
    };

    if (req_len >= sizeof(hid_keyboard_report_t)) {
        memcpy(buf, &report, sizeof(report));
        return sizeof(report);
    }

    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buf,
                           uint16_t buf_len) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_set_report_cb(): id = %u, type = %u, buffer = [ ", report_id, report_type);
    for (uint16_t i = 0; i < buf_len; i++) {
        printf("%02x ", buf[i]);
    }
    printf("]\n");

    if (report_id == HID_REPORT_ID_KEYBOARD && report_type == HID_REPORT_TYPE_OUTPUT && buf_len) {
        board_led_write(buf[0] & KEYBOARD_LED_CAPSLOCK);
    }
}

void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_set_protocol_cb(): protocol = %u\n", protocol);
}

bool tud_hid_set_idle_cb(uint8_t instance, uint8_t idle_rate) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_set_idle_cb(): idle_rate = %u\n", idle_rate);
    return true;
}
