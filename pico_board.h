/*
 * @Data  : 2022/08/06
 * @File  : pico_board.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "pico_layout.h"
#include "tusb.h"

#define PICO_BOARD_TREMBLING 5 /* 5ms */

#define PICO_BOARD_GPIO_IN_MASK 0x00FFFF
#define PICO_BOARD_GPIO_OUT_MASK 0xFF0000

struct pico_hid_report {
    uint8_t size;
    union {
        uint8_t               raw[CFG_TUD_HID_EP_BUFSIZE];
        hid_keyboard_report_t keyboard;
    } data;
};

typedef struct pico_board {
    struct pico_hid_report hid_report;
    uint8_t                hid_is_busy;
    uint8_t                hid_protocol;
    uint8_t                hid_idle_rate;
    uint32_t               hid_last_report_time;

    uint8_t round;
    uint8_t count;
    uint8_t pressed[6];

    uint16_t input_states[PICO_BOARD_TREMBLING][PICO_BOARD_NUM_ROWS]; /* Ring buffer */
} pico_board_t;

extern pico_board_t pico_board;

void pico_board_init();
void pico_board_task();
