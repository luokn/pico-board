/*
 * @Data  : 2022/08/06
 * @File  : pico_board.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "pico_layout.h"
#include "tusb.h"

/* Keyboard trembling delay. */
#define PICO_BOARD_TREMBLING 5 /* = 5ms */

/* Keyboard input pins: 8 ~ 15 */
#define PICO_BOARD_COL_BASE 8
#define PICO_BOARD_COL_PINS 16
#define PICO_BOARD_COL_MASK 0xFFFF00

/* Keyboard output pins: 2 ~ 7 */
#define PICO_BOARD_ROW_BASE 2
#define PICO_BOARD_ROW_PINS 6
#define PICO_BOARD_ROW_MASK 0xFC

/**
 * @brief Pico board type.
 */
typedef struct {
    uint8_t  hid_report[CFG_TUD_HID_EP_BUFSIZE];
    uint64_t hid_report_time;
    uint8_t  hid_report_id;
    uint8_t  hid_protocol;
    uint8_t  hid_idle_rate;

    uint8_t  round;
    uint16_t inputs[PICO_BOARD_TREMBLING][PICO_BOARD_NUM_ROWS]; /* Ring buffer */
} pico_board_t;

void pico_board_init();
void pico_board_task();
