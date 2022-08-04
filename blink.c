#include "blink.h"

#include <stdbool.h>

#include "bsp/board.h"

static uint32_t _blink_interval = BLINK_NOT_MOUNTED;

void led_blink_task() {
    static bool     state     = false;
    static uint32_t prev_time = 0;
    uint32_t        curr_time = board_millis();

    /*  Blink every interval ms */
    if (curr_time >= prev_time + _blink_interval) {
        board_led_write(state);

        prev_time = curr_time;
        state     = !state; /* toggle */
    }
}

void blink_set_pattern(enum blink_pattern pattern) {
    _blink_interval = pattern;
}

enum blink_pattern blink_get_pattern() {
    return _blink_interval;
}
