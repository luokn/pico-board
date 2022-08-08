/*
 * @Data  : 2022/08/06
 * @File  : usb_descriptors.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#pragma once

#include <stdint.h>

#define HID_REPORT_ID_KEYBOARD 1 /* Keyboard report ID */
#define HID_REPORT_ID_MOUSE 2    /* Mouse report ID */
#define HID_REPORT_ID_CONSUMER 3 /* Consumer control report ID */
#define HID_REPORT_ID_GAMEPAD 4  /* Gamepad report ID */

extern const uint8_t*   usb_device_desc;      // USB device descriptor
extern const uint8_t*   usb_config_desc;      // USB configuration descriptor
extern const uint8_t*   hid_report_desc;      // HID report descriptor
extern const uint16_t** usb_string_desc;      // USB string descriptor
extern const uint8_t    usb_string_desc_len;  // USB string descriptor length
