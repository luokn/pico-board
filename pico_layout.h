/*
 * @Data  : 2022/08/07
 * @File  : keymap.h
 * @Author: Kun Luo
 * @Email : luokun485@gmail.com
 */

#include <stdint.h>

#include "tusb.h"

#define PICO_BOARD_NUM_ROWS 6  /* 6 rows */
#define PICO_BOARD_MAX_COLS 16 /* Max to 16 columns */

#define PICO_BOARD_KEY_FN 0xF0 /* Fn key */

extern const uint8_t* pico_layout;
