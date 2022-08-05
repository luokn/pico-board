#pragma once

#include <stdint.h>

#define KEYBOARD_REPORT_ID 1 /* Keyboard report ID */
#define MOUSE_REPORT_ID 2    /* Mouse report ID */
#define CONSUMER_REPORT_ID 3 /* Consumer control report ID */
#define GAMEPOAD_REPORT_ID 4 /* Gamepad report ID */

void hid_report_task();

// void hid_report_send(uint8_t report_id, uint32_t btn);
