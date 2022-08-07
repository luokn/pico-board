#include "pico_layout.h"

static const uint8_t keyboard_row_1[] = {
    HID_KEY_ESCAPE, /* ESC */
    HID_KEY_F1,     /* F1 */
    HID_KEY_F2,     /* F2 */
    HID_KEY_F3,     /* F3 */
    HID_KEY_F4,     /* F4 */
    HID_KEY_F5,     /* F5 */
    HID_KEY_F6,     /* F6 */
    HID_KEY_F7,     /* F7 */
    HID_KEY_F8,     /* F8 */
    HID_KEY_F9,     /* F9 */
    HID_KEY_F10,    /* F10 */
    HID_KEY_F11,    /* F11 */
    HID_KEY_F12,    /* F12 */
    HID_KEY_INSERT, /* INSERT */
    HID_KEY_DELETE, /* DELETE */
};

static const uint8_t keyboard_row_2[] = {
    HID_KEY_GRAVE,     /* ` or ~ */
    HID_KEY_1,         /* 1 or ! */
    HID_KEY_2,         /* 2 or @ */
    HID_KEY_3,         /* 3 or # */
    HID_KEY_4,         /* 4 or $ */
    HID_KEY_5,         /* 5 or % */
    HID_KEY_6,         /* 6 or ^ */
    HID_KEY_7,         /* 7 or & */
    HID_KEY_8,         /* 8 or * */
    HID_KEY_9,         /* 9 or ( */
    HID_KEY_0,         /* 0 or ) */
    HID_KEY_MINUS,     /* - or _ */
    HID_KEY_EQUAL,     /* = or + */
    HID_KEY_BACKSPACE, /* Backspace */
};

static const uint8_t keyboard_row_3[] = {
    HID_KEY_TAB,           /* Tab */
    HID_KEY_Q,             /* Q or q */
    HID_KEY_W,             /* W or w */
    HID_KEY_E,             /* E or e */
    HID_KEY_R,             /* R or r */
    HID_KEY_T,             /* T or t */
    HID_KEY_Y,             /* Y or y */
    HID_KEY_U,             /* U or u */
    HID_KEY_I,             /* I or i */
    HID_KEY_O,             /* O or o */
    HID_KEY_P,             /* P or p */
    HID_KEY_BRACKET_LEFT,  /* [ or { */
    HID_KEY_BRACKET_RIGHT, /* ] or } */
    HID_KEY_BACKSLASH,     /* \ or | */
};

static const uint8_t keyboard_row_4[] = {
    HID_KEY_CAPS_LOCK,  /* Caps Lock */
    HID_KEY_A,          /* A or a */
    HID_KEY_S,          /* S or s */
    HID_KEY_D,          /* D or d */
    HID_KEY_F,          /* F or f */
    HID_KEY_G,          /* G or g */
    HID_KEY_H,          /* H or h */
    HID_KEY_J,          /* J or j */
    HID_KEY_K,          /* K or k */
    HID_KEY_L,          /* L or l */
    HID_KEY_SEMICOLON,  /* ; or : */
    HID_KEY_APOSTROPHE, /* ' or " */
    HID_KEY_ENTER,      /* Enter */
};

static const uint8_t keyboard_row_5[] = {
    HID_KEY_SHIFT_LEFT,  /* Left Shift */
    HID_KEY_Z,           /* Z or z */
    HID_KEY_X,           /* X or x */
    HID_KEY_C,           /* C or c */
    HID_KEY_V,           /* V or v */
    HID_KEY_B,           /* B or b */
    HID_KEY_N,           /* N or n */
    HID_KEY_M,           /* M or m */
    HID_KEY_COMMA,       /* , or < */
    HID_KEY_PERIOD,      /* . or > */
    HID_KEY_SLASH,       /* / or ? */
    HID_KEY_SHIFT_RIGHT, /* Right Shift */
    HID_KEY_ARROW_UP,    /* Up Arrow */
};

static const uint8_t keyboard_row_6[] = {
    HID_KEY_CONTROL_LEFT,  /* Left Control */
    PICO_BOARD_KEY_FN,     /* FN */
    HID_KEY_GUI_LEFT,      /* Left Windows */
    HID_KEY_ALT_LEFT,      /* Left Alt */
    HID_KEY_SPACE,         /* Space */
    HID_KEY_ALT_RIGHT,     /* Right Alt */
    HID_KEY_CONTROL_RIGHT, /* Right Control */
    HID_KEY_ARROW_LEFT,    /* Left Arrow */
    HID_KEY_ARROW_DOWN,    /* Down Arrow */
    HID_KEY_ARROW_UP,      /* Up Arrow */
};

const uint8_t* pico_layout[PICO_BOARD_NUM_ROWS] = {
    keyboard_row_1, keyboard_row_2, keyboard_row_3, keyboard_row_4, keyboard_row_5, keyboard_row_6,
};
