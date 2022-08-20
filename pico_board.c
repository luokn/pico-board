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

static size_t _pico_board_scan(uint8_t *keys, size_t max_keys);
static void   _pico_board_press(uint8_t *keys, size_t count);
static void   _pico_board_release();

static pico_board_t _board = {0};

void pico_board_init() {
    /* Setup stdio. */
    stdio_init_all();

    /* Setup usb. */
    tusb_init();
    printf("\x1b[1;32m[USB]\x1b[0m tusb_init()\n");

    /* Setup input gpios. */
    for (size_t i = 0; i < PICO_BOARD_COL_PINS; i++) {
        gpio_init(PICO_BOARD_COL_BASE + i);
        gpio_set_dir(PICO_BOARD_COL_BASE + i, GPIO_IN);
        gpio_pull_down(PICO_BOARD_COL_BASE + i);
    }

    /* Setup output gpios. */
    for (size_t i = 0; i < PICO_BOARD_ROW_PINS; i++) {
        gpio_init(PICO_BOARD_ROW_BASE + i);
        gpio_set_dir(PICO_BOARD_ROW_BASE + i, GPIO_OUT);
        gpio_put(PICO_BOARD_ROW_BASE + i, 0);
    }
}

void pico_board_task() {
    uint32_t start_us = timer_hw->timerawl;
    /* ==================================== */

    /* Process usb events. */
    tud_task();

    /* Scan the keyboard. */
    uint8_t keys[6];
    size_t  count = _pico_board_scan(keys, sizeof(keys));

    /* Process keyboard events. */
    if (count) {
        _pico_board_press(keys, count);
    } else {
        _pico_board_release();
    }

    /* ==================================== */
    while (timer_hw->timerawl - start_us < 1000) {
        tight_loop_contents();
    }
}

static size_t _pico_board_scan(uint8_t *keys, size_t max_keys) {
    size_t pressed_keys = 0;

    /* Next round. */
    _board.round++;
    if (_board.round >= PICO_BOARD_TREMBLING) {
        _board.round = 0;
    }

    /* Scan the keyboard. */
    for (size_t row = 0; row < PICO_BOARD_ROW_PINS; row++) {
        /* Select row */
        gpio_put_masked(PICO_BOARD_ROW_MASK, 1U << (PICO_BOARD_ROW_BASE + row));

        /* Delay 10 us, wait for the row to stabilize and prevent parasitic capacitance. */
        busy_wait_us_32(10);

        /* Readout gpio input states. */
        const uint16_t in_state = (gpio_get_all() & PICO_BOARD_COL_MASK) >> PICO_BOARD_COL_BASE;

        /* Get current state and previous state from the instance. */
        const uint16_t curr_state = _board.curr_states[row];
        const uint16_t prev_state = _board.prev_states[row][_board.round];

        /* XOR to get the bits that changed and the bits that remained the same. */
        const uint16_t changed_bits   = prev_state ^ in_state;
        const uint16_t unchanged_bits = ~changed_bits;

        /* Get value of changed bits from current state and get value of unchanged bits from previous state. */
        const uint16_t new_state = (curr_state & changed_bits) | (prev_state & unchanged_bits);

        if (new_state) { /* Scan the columns if new_state is not zero. */
            for (size_t col = 0; col < PICO_BOARD_COL_PINS; col++) {
                if (new_state & (1U << col)) {
                    keys[pressed_keys++] = pico_layout[(row << 4) | col];
                    if (pressed_keys == max_keys) return pressed_keys; /* If we have enough keys, return. */
                }
            }
        }

        _board.curr_states[row]               = new_state;
        _board.prev_states[row][_board.round] = in_state;
    }

    return pressed_keys;
}

static void _pico_board_press(uint8_t *keys, size_t count) {
    if (!tud_hid_ready()) return;

    /* Generate keyboard report. */
    hid_keyboard_report_t report = {0};
    memcpy(report.keycode, keys, count);

    /* Compare with previous report. */
    if (memcmp(&report, _board.hid_report, sizeof(hid_keyboard_report_t)) != 0) {
        printf("\x1b[1;32m[KEY]\x1b[0m _pico_board_scan(): [ ");
        for (size_t i = 0; i < count; i++) {
            printf("%02X ", keys[i]);
        }
        printf("]\n");

        /* Save current report. */
        _board.hid_report_id   = HID_REPORT_ID_KEYBOARD;
        _board.hid_report_size = sizeof(hid_keyboard_report_t);
        memcpy(_board.hid_report, &report, sizeof(hid_keyboard_report_t));

        /* Send the report. */
        tud_hid_report(HID_REPORT_ID_KEYBOARD, _board.hid_report, _board.hid_report_size);
    }
}

static void _pico_board_release() {
    if (!tud_hid_ready()) return;

    switch (_board.hid_report_id) {
        case HID_REPORT_ID_KEYBOARD: {
            printf("\x1b[1;32m[KEY]\x1b[0m _pico_board_scan(): []\n");

            /* Clear current report. */
            _board.hid_report_id   = HID_REPORT_ID_NONE;
            _board.hid_report_size = sizeof(hid_keyboard_report_t);
            memset(_board.hid_report, 0, sizeof(hid_keyboard_report_t));

            /* Send the report. */
            tud_hid_report(HID_REPORT_ID_KEYBOARD, _board.hid_report, _board.hid_report_size);
            break;
        }
        case HID_REPORT_ID_CONSUMER: {
            /* Clear current report. */
            _board.hid_report_id   = HID_REPORT_ID_NONE;
            _board.hid_report_size = sizeof(uint16_t);
            memset(_board.hid_report, 0, sizeof(uint16_t));

            /* Send the report. */
            tud_hid_report(HID_REPORT_ID_CONSUMER, _board.hid_report, _board.hid_report_size);
            break;
        }
        default: break;
    }
}
