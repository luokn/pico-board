/*
 * @Data  : 2022/08/06
 * @File  : usb_callbacks.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include <stdbool.h>
#include <stdio.h>

#include "usb_descriptors.h"

/*
 * USB 字符串描述符 回调函数
 */
const uint8_t* tud_descriptor_device_cb(void) {
    return usb_device_desc;
}

/*
 * USB 配置描述符 回调函数
 */
uint8_t const* tud_descriptor_configuration_cb(uint8_t index) {
    // This example use the same configuration for both high and full speed mode
    return usb_config_desc;
}

/*
 * HID 报文描述符 回调函数
 */
uint8_t const* tud_hid_descriptor_report_cb(uint8_t instance) {
    return hid_report_desc;
}

/*
 * USB 字符串描述符 回调函数
 */
const uint16_t* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    return index < usb_string_desc_len ? usb_string_desc[index] : NULL;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb() {
    printf("\x1b[1;32m[USB]\x1b[0m tud_mount_cb()\n");
}

// Invoked when device is unmounted
void tud_umount_cb() {
    printf("\x1b[1;32m[USB]\x1b[0m tud_umount_cb()\n");
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
    printf("\x1b[1;32m[USB]\x1b[0m tud_suspend_cb(): remote_wakeup_enabled = %s\n",
           remote_wakeup_en ? "true" : "false");
}

// Invoked when usb bus is resumed
void tud_resume_cb() {
    printf("\x1b[1;32m[USB]\x1b[0m tud_resume_cb()\n");
}
