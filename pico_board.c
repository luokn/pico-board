/*
 * @Data  : 2022/08/06
 * @File  : pico_board.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "pico_board.h"

#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "usb_descriptors.h"

// #define USB 1

pico_board_t pico_board = {0};

/* 8 ~ 15 */
const uint32_t _gpio_in_base = 8;
const uint32_t _gpio_in_pins = 16;
const uint32_t _gpio_in_mask = 0xFFFF00;

/* 2 ~ 7 */
const uint32_t _gpio_out_base = 2;
const uint32_t _gpio_out_pins = 6;
const uint32_t _gpio_out_mask = 0xFC;

static size_t _pico_board_scan(pico_board_t *board, uint8_t *keys, size_t max_keys);

void pico_board_init() {
    /* Setup input gpios. */
    for (size_t i = 0; i < _gpio_in_pins; i++) {
        gpio_init(_gpio_in_base + i);
        gpio_set_dir(_gpio_in_base + i, GPIO_IN);
        gpio_pull_down(_gpio_in_base + i);
    }

    /* Setup output gpios. */
    for (size_t i = 0; i < _gpio_out_pins; i++) {
        gpio_init(_gpio_out_base + i);
        gpio_set_dir(_gpio_out_base + i, GPIO_OUT);
        gpio_put(_gpio_out_base + i, 0);
    }

    /* Setup stdio. */
    stdio_init_all();

#ifdef USB
    /* Setup USB. */
    tusb_init();
    printf("\x1b[1;32m[USB]\x1b[0m tusb_init()\n");
#endif
}

void pico_board_task() {
    for (;;) {
        uint64_t start_us = time_us_64();
        /* ==================================== */

#ifdef USB
        /* Process usb events. */
        tud_task();
#endif

        /* Scan the keyboard. */
        uint8_t keys[6];
        size_t  num_keys = _pico_board_scan(&pico_board, keys, sizeof(keys));

        if (num_keys) {
            printf("\x1b[1;32m[KEY]:\x1b[0m [");
            for (size_t i = 0; i < num_keys; i++) {
                printf("%02X ", keys[i]);
            }
            printf("]\n");

            hid_keyboard_report_t report = {0};
            memcpy(report.keycode, keys, num_keys);

            if (memcmp(&report, &pico_board.hid_report, sizeof(report)) != 0) {
                pico_board.hid_report_id   = HID_REPORT_ID_KEYBOARD;
                pico_board.hid_report_time = start_us;
                memcpy(&pico_board.hid_report, &report, sizeof(report));

#ifdef USB

                if (tud_hid_ready()) {
                    tud_hid_report(pico_board.hid_report_id, &pico_board.hid_report, sizeof(report));
                }
#endif
            }
        } else {
            switch (pico_board.hid_report_id) {
                case HID_REPORT_ID_KEYBOARD: {
                    pico_board.hid_report_id   = HID_REPORT_ID_NONE;
                    pico_board.hid_report_time = start_us;
                    memset(&pico_board.hid_report, 0, sizeof(hid_keyboard_report_t));
#ifdef USB
                    if (tud_hid_ready()) {
                        tud_hid_report(pico_board.hid_report_id, &pico_board.hid_report, sizeof(hid_keyboard_report_t));
                    }
#endif
                }
                case HID_REPORT_ID_CONSUMER: {
                    pico_board.hid_report_id   = HID_REPORT_ID_NONE;
                    pico_board.hid_report_time = start_us;
                    memset(&pico_board.hid_report, 0, sizeof(uint16_t));
#ifdef USB
                    if (tud_hid_ready()) {
                        tud_hid_report(pico_board.hid_report_id, &pico_board.hid_report, sizeof(uint16_t));
                    }
#endif
                }
                default: break;
            }
        }

        /* ==================================== */
        uint32_t elapsed_us = time_us_64() - start_us;
        if (elapsed_us < 1000 * 1000U) {
            busy_wait_us_32(1000 * 1000U - elapsed_us);
        }
    }
}

static size_t _pico_board_scan(pico_board_t *board, uint8_t *keys, size_t max_keys) {
    size_t count = 0;

    board->round++;
    if (board->round >= PICO_BOARD_NUM_ROWS) {
        board->round = 0;
    }

    for (size_t row = 0; row < _gpio_out_pins; row++) {
        /* Select row */
        gpio_put_masked(_gpio_out_mask, 1U << (_gpio_out_base + row));

        /* Delay 10 us, wait for the row to stabilize and prevent parasitic capacitance. */
        busy_wait_us_32(10);

        /* Readout input pins.  */
        uint32_t input = gpio_get_all() & _gpio_in_mask;
        input >>= _gpio_in_base;

        /* Save current input state. */
        uint32_t prev_input              = board->inputs[board->round][row];
        board->inputs[board->round][row] = input;

        /* XOR to get mask and find the unchanged bits. */
        input &= ~(input ^ prev_input);

        for (size_t col = 0; col < _gpio_in_pins; col++, input >> 1) {
            if (input & 1U) {
                keys[count++] = pico_layout[row][col];

                /* If we have enough keys, return. */
                if (count == max_keys) return count;
            }
        }
    }

    return count;
}
