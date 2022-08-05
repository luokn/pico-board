#include <stddef.h>
#include <stdio.h>

#include "blink.h"
#include "bsp/board.h"
#include "hid_report.h"

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len) {
    // uint8_t next_report_id = report[0] + 1;

    // if (next_report_id < REPORT_ID_COUNT) {
    //     hid_report_send(next_report_id, board_button_read());
    // }

    uint8_t report_id = report[0];

    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_report_complete_cb(): id = %u, report = [", report_id);
    for (uint8_t i = 1; i < len; i++) {
        printf("%02x ", report[i]);
    }
    printf("]\n");
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer,
                               uint16_t reqlen) {
    // TODO not Implemented

    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_get_report_cb(): id = %u, type = %u\n", report_id, report_type);
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer,
                           uint16_t bufsize) {
    printf("\x1b[1;35m[HID]\x1b[0m tud_hid_set_report_cb(): id = %u, type = %u\n", report_id, report_type);

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
