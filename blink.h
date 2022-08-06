/*
 * @Data  : 2022/08/06
 * @File  : blink.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#pragma once

#include <stdint.h>

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum blink_pattern {
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED     = 1000,
    BLINK_SUSPENDED   = 2500,
};

void               led_blink_task();
void               blink_set_pattern(enum blink_pattern);
enum blink_pattern blink_get_pattern();
