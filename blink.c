/*
 * @Data  : 2022/08/06
 * @File  : blink.c
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include "blink.h"

#include <stdbool.h>

#include "bsp/board.h"

static uint32_t _interval    = BLINK_NOT_MOUNTED;
static uint32_t _last_time   = 0;
static bool     _blink_state = false;

void led_blink_task() {
    uint32_t now = board_millis();
    if (now - _last_time < _interval) return;

    /*  Blink every interval ms */
    board_led_write(_blink_state);

    /* toggle */
    _blink_state = !_blink_state;

    _last_time = now;
}

void blink_set_pattern(enum blink_pattern pattern) {
    _interval = pattern;
}

enum blink_pattern blink_get_pattern() {
    return _interval;
}
