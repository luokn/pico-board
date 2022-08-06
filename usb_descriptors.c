/*
 * @Data  : 2022/08/06
 * @File  : usb_descriptors.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "usb_descriptors.h"

#include "hid_report.h"
#include "tusb.h"

static const uint16_t _usb_version    = 0x0200; /* USB 2.0 */
static const uint16_t _vendor_id      = 0xabcd; /* 厂商ID */
static const uint16_t _product_id     = 0x0001; /* 产品ID */
static const uint16_t _device_release = 0x0001; /* 版本号 */

/*
 +---------------------------------+
 |      USB 字符串描述符            |
 + --------------------------------+
*/

/* 字符串值，UTF-16LE 编码 */
static uint16_t _language_string_desc[]    = {0x0304, 0x0409};                                      /* EN = 0x0409 */
static uint16_t _manufacture_string_desc[] = {0x0310, 'L', 'u', 'o', ' ', 'K', 'u', 'n'};           /* "Luo Kun" */
static uint16_t _product_string_desc[]     = {0x0314, 'P', 'i', 'c', 'o', 'B', 'o', 'a', 'r', 'd'}; /* "Picoboard" */
static uint16_t _serial_string_desc[]      = {0x0310, 'r', 'p', '2', '0', '0', '2', '0'};           /* "rp2020" */

const uint8_t _language_string_id    = 0; /* 字符串索引 0，语言 */
const uint8_t _manufacture_string_id = 1; /* 字符串索引 1，厂商 */
const uint8_t _product_string_id     = 2; /* 字符串索引 2，产品 */
const uint8_t _serial_string_id      = 3; /* 字符串索引 3，序列号 */

/* USB 字符串描述符 */
static const uint16_t* _usb_string_desc[] = {
    [0] = _language_string_desc,
    [1] = _manufacture_string_desc,
    [2] = _product_string_desc,
    [3] = _serial_string_desc,
};

/*
 +---------------------------------------------+
 |              USB 设备描述符                  |
 +---------------------------------------------+
*/

static const tusb_desc_device_t _usb_device_desc = {
    .bLength         = sizeof(tusb_desc_device_t), /* 设备描述符长度，固定为18 */
    .bDescriptorType = TUSB_DESC_DEVICE,           /* 描述符类型，固定为设备描述符 1 */
    .bcdUSB          = _usb_version,               /* USB版本，固定为 2.0 */

    .bDeviceClass    = 0x00,                   /* 设备类别，HID不在设备描述符中定义，固定为 0 */
    .bDeviceSubClass = 0x00,                   /* 设备子类别，HID不在设备描述符中定义，固定为 0 */
    .bDeviceProtocol = 0x00,                   /* 设备协议，HID不在设备描述符中定义，固定为 0 */
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE, /* 端点0最大包大小，固定为 64 */

    .idVendor  = _vendor_id,      /* 厂商ID */
    .idProduct = _product_id,     /* 产品ID */
    .bcdDevice = _device_release, /* 版本号 */

    .iManufacturer = _manufacture_string_id, /* 厂商的字符描述符索引 */
    .iProduct      = _product_string_id,     /* 产品的字符描述符索引 */
    .iSerialNumber = _serial_string_id,      /* 序列号的字符描述符索引 */

    .bNumConfigurations = 1, /* 配置描述符数量，固定为 1 */
};

/*
 +-------------------------------------+
 |          HID 报文描述符              |
 +-------------------------------------+
*/

static const uint8_t _hid_report_desc[] = {
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(KEYBOARD_REPORT_ID)), /* HID报文描述符：键盘报文 */
    // TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(REPORT_ID_MOUSE)),       /* HID报文描述符：鼠标报文 */
    TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(CONSUMER_REPORT_ID)), /* HID报文描述符：用户控制报文 */
    // TUD_HID_REPORT_DESC_GAMEPAD(HID_REPORT_ID(REPORT_ID_GAMEPAD)),   /* HID报文描述符：游戏报文 */
};

/*
 +------------------------------------------------+
 |              USB 配置描述符                     |
 +------------------------------------------------+
*/

const uint8_t _input_endpoint_address = 0x81; /* 端点地址，IN端点，端点1 */
// const uint8_t _output_endpoint_address = 0x02; /* 端点地址，OUT端点，端点2 */

static const uint8_t _usb_config_desc[] = {
    TUD_CONFIG_DESCRIPTOR(
        /*
         * USB 配置描述符
         */

        1,                                      /* 配置编号: 1 */
        1,                                      /* 接口数量: 1 */
        0,                                      /* 字符索引: 0(无字符串) */
        TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN, /* 总共长度: USB + HID */
        TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP,     /* 供电特性: 远程唤醒 */
        98                                      /* 电源电流: 98mA */
        ),

    TUD_HID_DESCRIPTOR(
        /*
         * USB 接口描述符
         */

        0,                         /* 接口编号: 0 */
        0,                         /* 字符索引: 0(无字符串) */
        HID_ITF_PROTOCOL_KEYBOARD, /* 协议类型: HID Boot 键盘 */
        sizeof(_hid_report_desc),  /* HID报文描述符长度 */

        /*
         * USB 配置描述符 + HID 报文描述符 + 输入端点描述符
         */

        _input_endpoint_address, /* 端点描述符：输入地址 */
        CFG_TUD_HID_EP_BUFSIZE,  /* 端点描述符：缓冲大小(16B)*/
        4                        /* 端点描述符：主机轮询间隔(4ms) */
        ),
};

const uint8_t*   usb_device_desc     = (const uint8_t*) &_usb_device_desc;
const uint8_t*   usb_config_desc     = _usb_config_desc;
const uint8_t*   hid_report_desc     = _hid_report_desc;
const uint16_t** usb_string_desc     = _usb_string_desc;
const uint8_t    usb_string_desc_len = sizeof(_usb_string_desc) / sizeof(_usb_string_desc[0]);
