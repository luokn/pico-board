/*
 * @Data  : 2022/08/06
 * @File  : pico_board.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "pico_board.h"

#include "hardware/gpio.h"
#include "usb_descriptors.h"

pico_board_t pico_board = {0};

static inline uint8_t _pico_board_scan(pico_board_t *board, uint8_t keys[6]) {
    uint8_t num_keys = 0;

    board->round++;
    if (board->round >= PICO_BOARD_NUM_ROWS) {
        board->round = 0;
    }

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
                keys[num_keys++] = pico_layout[row][col];
            }
        }

        /* Save current state to the scanned results. */
        board->input_states[board->round][row] = state;
    }

    return num_keys;
}

void _pico_board_set_keys(pico_board_t *board, const uint8_t *keys, uint8_t num_keys) {
    pico_board.num_keys = num_keys;
    memcpy(pico_board.keys, keys, num_keys);
}

void _pico_board_gen_report(pico_board_t *board) {
    pico_board.hid_report.size                   = sizeof(hid_keyboard_report_t);
    pico_board.hid_report.data.keyboard.modifier = 0;
    pico_board.hid_report.data.keyboard.reserved = 0;
    memcpy(pico_board.hid_report.data.keyboard.keycode, pico_board.keys, pico_board.num_keys);
}

void _pico_board_send_report(pico_board_t *board) {
    if (tud_hid_ready()) {
        tud_hid_n_report(0, HID_REPORT_ID_KEYBOARD, &pico_board.hid_report, pico_board.hid_report.size);

        pico_board.hid_last_report_time = time_us_64();
    }
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

        uint8_t keys[6]  = {0};
        uint8_t num_keys = _pico_board_scan(&pico_board, keys);

        if (num_keys) {
            /*
             * If there is any key pressed, we should send the report to the host, excluding the hi_idle_rate is not 0.
             */
            if (num_keys != pico_board.num_keys || memcmp(keys, pico_board.keys, num_keys) != 0) {
                _pico_board_gen_report(&pico_board);
                _pico_board_send_report(&pico_board);
            }
        } else {
            /*
             * If there is no key pressed, we should send the empty report to the host.
             */
            if (pico_board.num_keys) {
                _pico_board_gen_report(&pico_board);
                _pico_board_send_report(&pico_board);
            }
        }

        /*
         * Copy pressed array to hid_report.data.keyboard.keys.
         */
        _pico_board_set_keys(&pico_board, keys, num_keys);

        /* ==================================== */
        uint32_t elapsed_us = time_us_64() - start_us;
        if (elapsed_us < 1000U) {
            busy_wait_us_32(1000U - elapsed_us);
        }
    }
}
