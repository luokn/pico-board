/*
 * @Data  : 2022/08/06
 * @File  : pico_board.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "pico_board.h"

#include "hardware/gpio.h"
#include "hid_report.h"

pico_board_t pico_board = {0};

static inline uint8_t _pico_board_scan(pico_board_t *board, int8_t pressed[6]) {
    board->round++;
    if (board->round >= PICO_BOARD_NUM_ROWS) {
        board->round = 0;
    }

    uint8_t count = 0;

    for (size_t row = 0; row < PICO_BOARD_NUM_ROWS; row++) {
        /* Select row */
        gpio_put_masked(PICO_BOARD_GPIO_OUT_MASK, 1U << row);

        /* Delay 10 us, wait for the row to stabilize and prevent parasitic capacitance. */
        busy_wait_us_32(10);

        /* Readout input pins.  */
        uint16_t prev_state = board->input_states[board->round][row];
        uint16_t state      = gpio_get_all() & PICO_BOARD_GPIO_IN_MASK;

        /* XOR to find the changed bits. */
        state &= ~(state ^ prev_state);

        for (size_t col = 0; col < 16; col++) {
            if (state & (1U << col)) {
                pressed[count++] = pico_layout[row][col];
            }
        }

        /* Save current state to the scanned results. */
        board->input_states[board->round][row] = state;
    }

    return count;
}

void pico_board_init() {
    gpio_set_dir_in_masked(PICO_BOARD_GPIO_IN_MASK);   /* Set Pin 0-15 as input. */
    gpio_set_dir_out_masked(PICO_BOARD_GPIO_OUT_MASK); /* Set Pin 16-23 as output. */

    gpio_put_masked(PICO_BOARD_GPIO_OUT_MASK, 0); /* Set Pin 16-23 as 0 */
}

void pico_board_task() {
    for (size_t i = 1;; ++i) {
        uint64_t start_us = time_us_64();
        /* ==================================== */

        uint8_t pressed[6] = {0};
        uint8_t count      = _pico_board_scan(&pico_board, pressed);

        if (count) {
            /*
             * If there is any key pressed, we should send the report to the host, excluding the hi_idle_rate is not 0.
             */
            if (count == pico_board.count && memcmp(pressed, pico_board.pressed, count) == 0) {
                if (i == pico_board.hid_idle_rate * 4) {
                    tud_hid_n_report(0, KEYBOARD_REPORT_ID, &pico_board.hid_report, pico_board.hid_report.size);
                }
            } else {
                pico_board.hid_report.size                   = sizeof(hid_keyboard_report_t);
                pico_board.hid_report.data.keyboard.modifier = 0;
                pico_board.hid_report.data.keyboard.reserved = 0;
                memcpy(pico_board.hid_report.data.keyboard.keycode, pressed, count);

                tud_hid_n_report(0, KEYBOARD_REPORT_ID, &pico_board.hid_report, pico_board.hid_report.size);
            }
        } else {
            /*
             * If there is no key pressed, we should send the empty report to the host.
             */
            if (pico_board.count) {
                pico_board.hid_report.size                   = sizeof(hid_keyboard_report_t);
                pico_board.hid_report.data.keyboard.modifier = 0;
                pico_board.hid_report.data.keyboard.reserved = 0;
                memset(pico_board.hid_report.data.keyboard.keycode, 0, count);

                tud_hid_n_report(0, KEYBOARD_REPORT_ID, &pico_board.hid_report, pico_board.hid_report.size);
            }
        }

        /*
         * Copy pressed array to hid_report.data.keyboard.keys.
         */
        pico_board.count = count;
        memcpy(pico_board.pressed, pressed, count);

        /* ==================================== */
        uint32_t elapsed_us = time_us_64() - start_us;
        if (elapsed_us < 1000U) {
            busy_wait_us_32(1000U - elapsed_us);
        }
    }
}
