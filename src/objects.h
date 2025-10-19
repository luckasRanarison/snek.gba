#ifndef OBJECTS_H
#define OBJECTS_H

#include "bitflags.h"
#include "constants.h"
#include "types.h"

#include <stdint.h>

typedef enum {
    SP_SHAPE_SQUARE,
    SP_SHAPE_HORIZONTAL_RECT,
    SP_SHAPE_VERTICAL_RECT,
} SpriteShape;

typedef enum {
    SP_MODE_NORMAL,
    SP_MODE_SEMI_TRANSPARENT,
    SP_MODE_WINDOW,
} SpriteMode;

typedef struct {
    uint16_t attr0;
    uint16_t attr1;
    uint16_t attr2;
    uint16_t attr3;
} Sprite;

#define DEFINE_ACCESSORS(attr, field, type, mask, shift) \
    inline void obj_set_##field(Sprite *sp, type val) {  \
        SET_BITS(sp->attr, mask, val, shift);            \
    }                                                    \
    inline type obj_get_##field(Sprite *sp) {            \
        return (type)GET_BITS(sp->attr, mask, shift);    \
    }

DEFINE_ACCESSORS(attr0, y, uint8_t, 0xFF, 0)
DEFINE_ACCESSORS(attr0, transform, uint8_t, 0b1, 8)
DEFINE_ACCESSORS(attr0, dbl_size, uint8_t, 0b1, 9)
DEFINE_ACCESSORS(attr0, mode, SpriteMode, 0b11, 10)
DEFINE_ACCESSORS(attr0, mosaic, uint8_t, 0b11, 12)
DEFINE_ACCESSORS(attr0, color_mode, ColorMode, 0b11, 13)
DEFINE_ACCESSORS(attr0, shape, SpriteShape, 0b11, 14)
DEFINE_ACCESSORS(attr1, x, uint16_t, 0x1FF, 0)
DEFINE_ACCESSORS(attr1, h_flip, uint8_t, 0b1, 12)
DEFINE_ACCESSORS(attr1, v_flip, uint8_t, 0b1, 13)
DEFINE_ACCESSORS(attr1, size, uint8_t, 0b11, 14)
DEFINE_ACCESSORS(attr2, tile, uint8_t, 0x3FF, 0)
DEFINE_ACCESSORS(attr2, priority, uint8_t, 0b11, 10)
DEFINE_ACCESSORS(attr2, palette, uint8_t, 0b1111, 12)

#endif // !OBJECTS_H
