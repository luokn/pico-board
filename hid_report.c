#include "hid_report.h"

#include <stddef.h>

#include "blink.h"
#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_report_task() {
    const uint32_t  interval  = 10; /* Poll every 10ms */
    static uint32_t prev_time = 0;
    uint32_t        curr_time = board_millis();

    if (curr_time - prev_time < interval) return; /* not enough time */
    prev_time = curr_time;

    if (tud_suspended()) return;

    static bool has_sent_report = false;

    if (board_button_read()) {
        if (!has_sent_report) {
            uint8_t keycode[6] = {HID_KEY_CAPS_LOCK, 0, 0, 0, 0, 0};
            tud_hid_keyboard_report(KEYBOARD_REPORT_ID, 0, keycode);
        }

        has_sent_report = true;
    } else {
        if (has_sent_report) {
            uint8_t keycode[6] = {0};
            tud_hid_keyboard_report(KEYBOARD_REPORT_ID, 0, keycode);
        }

        has_sent_report = false;
    }

    // // Remote wakeup
    // if (tud_suspended() && on) {
    //     // Wake up host if we are in suspend mode
    //     // and REMOTE_WAKEUP feature is enabled by host
    //     tud_remote_wakeup();
    // } else {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    // hid_report_send(REPORT_ID_KEYBOARD, on);

    // }
}

// static void _send_keyboard(uint32_t btn);
// static void _send_mouse(uint32_t btn);
// static void _send_consumer_control(uint32_t btn);
// static void _send_gamepad(uint32_t btn);

// void hid_report_send(uint8_t report_id, uint32_t btn) {
//     if (tud_hid_ready()) {
//         switch (report_id) {
//             case REPORT_ID_KEYBOARD: _send_keyboard(btn); break;
//             case REPORT_ID_MOUSE: _send_mouse(btn); break;
//             case REPORT_ID_CONSUMER_CONTROL: _send_consumer_control(btn); break;
//             case REPORT_ID_GAMEPAD: _send_gamepad(btn); break;
//             default: break;
//         }
//     }
//     /*  skip if hid is not ready yet */
// }

// static void _send_keyboard(uint32_t btn) {
//     // use to avoid send multiple consecutive zero report for keyboard
//     static bool has_keyboard_key = false;

//     if (btn) {
//         uint8_t keycode[6] = {0};
//         keycode[0]         = HID_KEY_A;

//         tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
//         has_keyboard_key = true;
//     } else {
//         // send empty key report if previously has key pressed
//         if (has_keyboard_key) {
//             tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
//         }
//         has_keyboard_key = false;
//     }
// }

// static void _send_mouse(uint32_t btn) {
//     int8_t const delta = 5;

//     // no button, right + down, no scroll, no pan
//     tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, delta, delta, 0, 0);
// }

// static void _send_consumer_control(uint32_t btn) {
//     // use to avoid send multiple consecutive zero report
//     static bool has_consumer_key = false;

//     if (btn) {
//         // volume down
//         uint16_t volume_down = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
//         tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_down, 2);
//         has_consumer_key = true;
//     } else {
//         // send empty key report (release key) if previously has key pressed
//         uint16_t empty_key = 0;
//         if (has_consumer_key) tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_key, 2);
//         has_consumer_key = false;
//     }
// }

// static void _send_gamepad(uint32_t btn) {
//     // use to avoid send multiple consecutive zero report for keyboard
//     static bool has_gamepad_key = false;

//     hid_gamepad_report_t report = {.x = 0, .y = 0, .z = 0, .rz = 0, .rx = 0, .ry = 0, .hat = 0, .buttons = 0};

//     if (btn) {
//         report.hat     = GAMEPAD_HAT_UP;
//         report.buttons = GAMEPAD_BUTTON_A;
//         tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));

//         has_gamepad_key = true;
//     } else {
//         report.hat     = GAMEPAD_HAT_CENTERED;
//         report.buttons = 0;
//         if (has_gamepad_key) tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
//         has_gamepad_key = false;
//     }
// }
