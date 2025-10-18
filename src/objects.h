#ifndef OBJECTS_H
#define OBJECTS_H

#include "bitflags.h"
#include "constants.h"
#include "types.h"

#include <stdint.h>

typedef enum {
    OBJ_SHAPE_SQUARE,
    OBJ_SHAPE_HORIZONTAL_RECT,
    OBJ_SHAPE_VERTICAL_RECT,
} OBJShape;

typedef enum {
    OBJ_MODE_NORMAL,
    OBJ_MODE_SEMI_TRANSPARENT,
    OBJ_MODE_WINDOW,
} OBJMode;

#define SET_OAM_ATTR(id, attr, mask, value) \
    SET_BITS(*((volatile uint16_t *)(ADDR_OAM) + attr + id * 4), mask, value)

inline void obj_set_y(uint8_t id, uint8_t y) {
    SET_OAM_ATTR(id, 0, 0xFF, y);
}

inline void obj_set_x(uint8_t id, uint16_t x) {
    SET_OAM_ATTR(id, 1, 0x1FF, x);
}

inline void obj_set_color_mode(uint8_t id, ColorMode mode) {
    SET_OAM_ATTR(id, 0, 0b11 << 12, mode);
}

inline void obj_set_shape(uint8_t id, OBJShape shape) {
    SET_OAM_ATTR(id, 0, 0b11 << 14, shape);
}

inline void obj_set_size(uint8_t id, uint8_t size) {
    SET_OAM_ATTR(id, 1, 0b11 << 14, size);
}

inline void obj_set_char(uint8_t id, uint16_t ch) {
    SET_OAM_ATTR(id, 2, 0x3FF, ch);
}

inline void obj_set_prio(uint8_t id, uint8_t prio) {
    SET_OAM_ATTR(id, 2, 0b11 << 10, prio);
}

inline void obj_set_pal(uint8_t id, uint8_t pal) {
    SET_OAM_ATTR(id, 2, 0b1111 << 12, pal);
}

#endif // !OBJECTS_H
