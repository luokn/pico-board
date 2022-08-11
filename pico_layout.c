#include "pico_layout.h"

static const uint8_t _layout[] = {
    /* Row 1 */
    [0x00] = HID_KEY_ESCAPE,    /* Esc */
    [0x01] = HID_KEY_GRAVE,     /* ` or ~ */
    [0x02] = HID_KEY_1,         /* 1 or ! */
    [0x03] = HID_KEY_2,         /* 2 or @ */
    [0x04] = HID_KEY_3,         /* 3 or # */
    [0x05] = HID_KEY_4,         /* 4 or $ */
    [0x06] = HID_KEY_5,         /* 5 or % */
    [0x07] = HID_KEY_6,         /* 6 or ^ */
    [0x08] = HID_KEY_7,         /* 7 or & */
    [0x09] = HID_KEY_8,         /* 8 or * */
    [0x0A] = HID_KEY_9,         /* 9 or ( */
    [0x0B] = HID_KEY_0,         /* 0 or ) */
    [0x0C] = HID_KEY_MINUS,     /* - or _ */
    [0x0D] = HID_KEY_EQUAL,     /* = or + */
    [0x0E] = HID_KEY_DELETE,    /* Delete */
    [0x0F] = HID_KEY_BACKSPACE, /* Backspace */

    /* Row 2 */
    [0x10] = HID_KEY_TAB,           /* Tab */
    [0x11] = HID_KEY_Q,             /* Q or q */
    [0x12] = HID_KEY_W,             /* W or w */
    [0x13] = HID_KEY_E,             /* E or e */
    [0x14] = HID_KEY_R,             /* R or r */
    [0x15] = HID_KEY_T,             /* T or t */
    [0x16] = HID_KEY_Y,             /* Y or y */
    [0x17] = HID_KEY_U,             /* U or u */
    [0x18] = HID_KEY_I,             /* I or i */
    [0x19] = HID_KEY_O,             /* O or o */
    [0x1A] = HID_KEY_P,             /* P or p */
    [0x1B] = HID_KEY_BRACKET_LEFT,  /* [ or { */
    [0x1C] = HID_KEY_BRACKET_RIGHT, /* ] or } */
    [0x1D] = HID_KEY_BACKSLASH,     /* \ or | */

    /* Row 3 */
    [0x20] = HID_KEY_CAPS_LOCK,  /* Caps Lock */
    [0x21] = HID_KEY_A,          /* A or a */
    [0x22] = HID_KEY_S,          /* S or s */
    [0x23] = HID_KEY_D,          /* D or d */
    [0x24] = HID_KEY_F,          /* F or f */
    [0x25] = HID_KEY_G,          /* G or g */
    [0x26] = HID_KEY_H,          /* H or h */
    [0x27] = HID_KEY_J,          /* J or j */
    [0x28] = HID_KEY_K,          /* K or k */
    [0x29] = HID_KEY_L,          /* L or l */
    [0x2A] = HID_KEY_SEMICOLON,  /* ; or : */
    [0x2B] = HID_KEY_APOSTROPHE, /* ' or " */
    [0x2C] = HID_KEY_ENTER,      /* Enter */

    /* Row 4 */
    [0x30] = HID_KEY_SHIFT_LEFT,  /* Left Shift */
    [0x31] = HID_KEY_Z,           /* Z or z */
    [0x32] = HID_KEY_X,           /* X or x */
    [0x33] = HID_KEY_C,           /* C or c */
    [0x34] = HID_KEY_V,           /* V or v */
    [0x35] = HID_KEY_B,           /* B or b */
    [0x36] = HID_KEY_N,           /* N or n */
    [0x37] = HID_KEY_M,           /* M or m */
    [0x38] = HID_KEY_COMMA,       /* , or < */
    [0x39] = HID_KEY_PERIOD,      /* . or > */
    [0x3A] = HID_KEY_SLASH,       /* / or ? */
    [0x3B] = HID_KEY_SHIFT_RIGHT, /* Right Shift */
    [0x3C] = HID_KEY_ARROW_UP,    /* Up Arrow */

    /* Row 5 */
    [0x40] = HID_KEY_CONTROL_LEFT,  /* Left Control */
    [0x41] = PICO_BOARD_KEY_FN,     /* FN */
    [0x42] = HID_KEY_GUI_LEFT,      /* Left Windows */
    [0x43] = HID_KEY_ALT_LEFT,      /* Left Alt */
    [0x44] = HID_KEY_SPACE,         /* Space */
    [0x45] = HID_KEY_ALT_RIGHT,     /* Right Alt */
    [0x46] = HID_KEY_CONTROL_RIGHT, /* Right Control */
    [0x47] = HID_KEY_ARROW_LEFT,    /* Left Arrow */
    [0x48] = HID_KEY_ARROW_DOWN,    /* Down Arrow */
    [0x49] = HID_KEY_ARROW_UP,      /* Up Arrow */
};

const uint8_t* pico_layout = _layout;
