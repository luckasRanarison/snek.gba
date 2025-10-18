#ifndef INPUT_H
#define INPUT_H

#include "register.h"

typedef enum {
    KEY_A     = (1 << 0),
    KEY_B     = (1 << 1),
    KEY_SELCT = (1 << 2),
    KEY_START = (1 << 3),
    KEY_RIGHT = (1 << 4),
    KEY_LEFT  = (1 << 5),
    KEY_UP    = (1 << 6),
    KEY_DOWN  = (1 << 7),
    KEY_R     = (1 << 8),
    KEY_L     = (1 << 9)
} InputKey;

inline int is_key_pressed(InputKey key) {
    return (*REG_KEYINPUT & key) != 0;
}

#endif // !INPUT_H
