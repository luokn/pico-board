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

#include "usb_descriptors.h"

#include "hid_report.h"
#include "tusb.h"

const uint16_t usb_version    = 0x0200; /* USB 2.0 */
const uint16_t vendor_id      = 0xabcd; /* 厂商ID */
const uint16_t product_id     = 0x0001; /* 产品ID */
const uint16_t device_release = 0x0001; /* 版本号 */

/*
 +---------------------------------+
 |      USB 字符串描述符            |
 + --------------------------------+
*/

/* 字符串值，UTF-16LE 编码 */
static uint16_t language_string_desc[]    = {0x0304, 0x0409};                                      /* EN = 0x0409 */
static uint16_t manufacture_string_desc[] = {0x0310, 'L', 'u', 'o', ' ', 'K', 'u', 'n'};           /* "Luo Kun" */
static uint16_t product_string_desc[]     = {0x0314, 'P', 'i', 'c', 'o', 'B', 'o', 'a', 'r', 'd'}; /* "Picoboard" */
static uint16_t serial_string_desc[]      = {0x0310, 'r', 'p', '2', '0', '0', '2', '0'};           /* "rp2020" */

const uint8_t language_string_id    = 0; /* 字符串索引 0，语言 */
const uint8_t manufacture_string_id = 1; /* 字符串索引 1，厂商 */
const uint8_t product_string_id     = 2; /* 字符串索引 2，产品 */
const uint8_t serial_string_id      = 3; /* 字符串索引 3，序列号 */

/* USB 字符串描述符 */
static const uint16_t* _string_desc[] = {
    [0] = language_string_desc,
    [1] = manufacture_string_desc,
    [2] = product_string_desc,
    [3] = serial_string_desc,
};

/*
 +---------------------------------------------+
 |              USB 设备描述符                  |
 +---------------------------------------------+
*/

static const tusb_desc_device_t _device_desc = {
    .bLength         = sizeof(tusb_desc_device_t), /* 设备描述符长度，固定为18 */
    .bDescriptorType = TUSB_DESC_DEVICE,           /* 描述符类型，固定为设备描述符 1 */
    .bcdUSB          = usb_version,                /* USB版本，固定为 2.0 */

    .bDeviceClass    = 0x00,                   /* 设备类别，HID不在设备描述符中定义，固定为 0 */
    .bDeviceSubClass = 0x00,                   /* 设备子类别，HID不在设备描述符中定义，固定为 0 */
    .bDeviceProtocol = 0x00,                   /* 设备协议，HID不在设备描述符中定义，固定为 0 */
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE, /* 端点0最大包大小，固定为 64 */

    .idVendor  = vendor_id,      /* 厂商ID */
    .idProduct = product_id,     /* 产品ID */
    .bcdDevice = device_release, /* 版本号 */

    .iManufacturer = manufacture_string_id, /* 厂商的字符描述符索引 */
    .iProduct      = product_string_id,     /* 产品的字符描述符索引 */
    .iSerialNumber = serial_string_id,      /* 序列号的字符描述符索引 */

    .bNumConfigurations = 1, /* 配置描述符数量，固定为 1 */
};

/*
 +-------------------------------------+
 |          HID 报文描述符              |
 +-------------------------------------+
*/

const uint8_t _hid_report_desc[] = {
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(REPORT_ID_KEYBOARD)),         /* HID报文描述符：键盘报文 */
    TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(REPORT_ID_MOUSE)),               /* HID报文描述符：鼠标报文 */
    TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(REPORT_ID_CONSUMER_CONTROL)), /* HID报文描述符：媒体报文 */
    TUD_HID_REPORT_DESC_GAMEPAD(HID_REPORT_ID(REPORT_ID_GAMEPAD)),           /* HID报文描述符：游戏报文 */
};

/*
 +------------------------------------------------+
 |              USB 配置描述符                     |
 +------------------------------------------------+
*/

static const uint8_t _config_desc[] = {
    TUD_CONFIG_DESCRIPTOR(
        /* config number    = */ 1,                                      /* 配置编号 1 */
        /* interface count  = */ 1,                                      /* 接口数量 1 */
        /* string index     = */ 0,                                      /* 字符串索引 0，无字符串 */
        /* total length     = */ TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN, /* 总长度，配置描述符长度 + HID描述符长度 */
        /* attribute        = */ TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, /* 配置属性，支持远程唤醒 */
        /* power in mA      = */ 100),                               /* 电源电流 100mA */

    TUD_HID_DESCRIPTOR(
        /* Interface number         = */ 0,                        /* 接口编号 0 */
        /* string index             = */ 0,                        /* 字符串索引 0，无字符串 */
        /* protocol                 = */ HID_ITF_PROTOCOL_NONE,    /* 无协议 */
        /* report descriptor len    = */ sizeof(_hid_report_desc), /* HID报文描述符长度 */

        /* EP In address    = */ 0x81, /* 端点描述符：地址及输入属性，bit 7为输入 1, bit 0-3与其他位为 0 */
        /* size             = */ CFG_TUD_HID_EP_BUFSIZE, /* 端点描述符：缓冲区大小为 16 bytes*/
        /* polling interval = */ 5),                     /* 端点描述符：主机轮询间隔为 5ms */
};

const uint8_t*   usb_device_desc     = (const uint8_t*) &_device_desc;
const uint8_t*   usb_config_desc     = _config_desc;
const uint8_t*   hid_report_desc     = _hid_report_desc;
const uint16_t** usb_string_desc     = _string_desc;
const uint8_t    usb_string_desc_len = sizeof(_string_desc) / sizeof(_string_desc[0]);
