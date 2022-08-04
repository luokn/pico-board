#pragma once

#include <stdint.h>

enum hid_report_id {
    REPORT_ID_KEYBOARD = 1,
    REPORT_ID_MOUSE    = 2,
    REPORT_ID_CONSUMER_CONTROL,
    REPORT_ID_GAMEPAD,
};

void hid_report_send(uint8_t report_id, uint32_t btn);
void hid_report_task();
