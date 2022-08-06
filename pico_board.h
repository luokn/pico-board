/*
 * @Data  : 2022/08/06
 * @File  : pico_board.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "tusb.h"

typedef struct pico_board {
    bool                  send_ok;
    uint32_t              hid_idle;
    hid_keyboard_report_t keyboard_report;
} pico_board_t;

extern pico_board_t pico_board;

void pico_board_init();
void pico_board_task();

void pico_board_press(const uint8_t *key);
