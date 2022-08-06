/*
 * @Data  : 2022/08/06
 * @File  : usb_descriptors.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#pragma once

#include <stdint.h>

extern const uint8_t*   usb_device_desc;      // USB device descriptor
extern const uint8_t*   usb_config_desc;      // USB configuration descriptor
extern const uint8_t*   hid_report_desc;      // HID report descriptor
extern const uint16_t** usb_string_desc;      // USB string descriptor
extern const uint8_t    usb_string_desc_len;  // USB string descriptor length
