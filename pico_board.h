/*
 * @Data  : 2022/08/06
 * @File  : pico_board.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "pico_layout.h"
#include "tusb.h"

#define PICO_BOARD_TREMBLING 5 /* 5ms */

typedef struct pico_board {
    uint8_t  hid_report[CFG_TUD_HID_EP_BUFSIZE];
    uint64_t hid_report_time;
    uint8_t  hid_report_id;
    uint8_t  hid_protocol;
    uint8_t  hid_idle_rate;

    uint8_t  round;
    uint16_t inputs[PICO_BOARD_TREMBLING][PICO_BOARD_NUM_ROWS]; /* Ring buffer */
} pico_board_t;

extern pico_board_t pico_board;

void pico_board_init();
void pico_board_task();
