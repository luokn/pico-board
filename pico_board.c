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

static inline size_t _pico_board_scan(pico_board_t *board, uint8_t *results) {
    size_t count = 0;

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
                results[count++] = pico_layout[row][col];
            }
        }

        /* Save current state to the scanned results. */
        board->input_states[board->round][row] = state;
    }

    return count;
}

void _pico_board_send_keyboard(pico_board_t *board, const uint8_t *keys, size_t num_keys) {
    // board->cur_result.num_keys = num_keys;

    // pico_board.hid_report.type                   = sizeof(hid_keyboard_report_t);
    // pico_board.hid_report.data.keyboard.modifier = 0;
    // pico_board.hid_report.data.keyboard.reserved = 0;
    // memcpy(pico_board.hid_report.data.keyboard.keycode, pico_board.cur_result.keys, pico_board.cur_result.num_keys);

    // if (tud_hid_ready()) {
    //     tud_hid_n_report(0, HID_REPORT_ID_KEYBOARD, &pico_board.hid_report, pico_board.hid_report.size);
    // }
}

void pico_board_init() {
    gpio_set_dir_in_masked(PICO_BOARD_GPIO_IN_MASK);   /* Set Pin 0-15 as input. */
    gpio_set_dir_out_masked(PICO_BOARD_GPIO_OUT_MASK); /* Set Pin 16-23 as output. */

    gpio_put_masked(PICO_BOARD_GPIO_OUT_MASK, 0); /* Set Pin 16-23 as 0 */

    tusb_init(); /* Init USB. */
}

void pico_board_task() {
    for (;;) {
        uint64_t start_us = time_us_64();
        /* ==================================== */

        /* Process usb events. */
        tud_task();

        /* Scan the keyboard. */
        uint8_t keys[128];
        size_t  num_keys = _pico_board_scan(&pico_board, keys);

        if (num_keys) {
            hid_keyboard_report_t report = {0};
            memcpy(report.keycode, keys, num_keys);

            if (memcmp(&report, &pico_board.hid_report, sizeof(report)) != 0) {
                pico_board.hid_report_id   = HID_REPORT_ID_KEYBOARD;
                pico_board.hid_report_time = start_us;
                memcpy(&pico_board.hid_report, &report, sizeof(report));

                if (tud_hid_ready()) {
                    tud_hid_report(pico_board.hid_report_id, &pico_board.hid_report, sizeof(report));
                }
            }
        } else {
            switch (pico_board.hid_report_id) {
                case HID_REPORT_ID_KEYBOARD: {
                    pico_board.hid_report_id   = HID_REPORT_ID_NONE;
                    pico_board.hid_report_time = start_us;
                    memset(&pico_board.hid_report, 0, sizeof(hid_keyboard_report_t));

                    if (tud_hid_ready()) {
                        tud_hid_report(pico_board.hid_report_id, &pico_board.hid_report, sizeof(hid_keyboard_report_t));
                    }
                }
                case HID_REPORT_ID_CONSUMER: {
                    pico_board.hid_report_id   = HID_REPORT_ID_NONE;
                    pico_board.hid_report_time = start_us;
                    memset(&pico_board.hid_report, 0, sizeof(uint16_t));

                    if (tud_hid_ready()) {
                        tud_hid_report(pico_board.hid_report_id, &pico_board.hid_report, sizeof(uint16_t));
                    }
                }
                default: break;
            }
        }

        /* ==================================== */
        uint32_t elapsed_us = time_us_64() - start_us;
        if (elapsed_us < 1000U) {
            busy_wait_us_32(1000U - elapsed_us);
        }
    }
}
