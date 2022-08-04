#include "blink.h"

#include <stdbool.h>

#include "bsp/board.h"

static uint32_t _blink_interval  = BLINK_NOT_MOUNTED;
static bool     _blink_state     = false;
static uint32_t _blink_last_time = 0;

void led_blink_task() {
    uint32_t now = board_millis();
    if (now - _blink_last_time < _blink_interval) return;

    /*  Blink every interval ms */
    board_led_write(_blink_state);

    /* toggle */
    _blink_state = !_blink_state;

    _blink_last_time = now;
}

void blink_set_pattern(enum blink_pattern pattern) {
    _blink_interval = pattern;
}

enum blink_pattern blink_get_pattern() {
    return _blink_interval;
}
