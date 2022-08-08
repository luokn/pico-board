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

struct _hid_report;
struct _scan_result;

typedef struct pico_board {
    uint8_t  hid_report[CFG_TUD_HID_EP_BUFSIZE];
    uint64_t hid_report_time;
    uint8_t  hid_report_id;
    uint8_t  hid_protocol;
    uint8_t  hid_idle_rate;

    uint8_t  round;
    uint16_t input_states[PICO_BOARD_TREMBLING][PICO_BOARD_NUM_ROWS]; /* Ring buffer */
} pico_board_t;

extern pico_board_t pico_board;

void pico_board_init();
void pico_board_task();
