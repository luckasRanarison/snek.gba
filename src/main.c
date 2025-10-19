// #include "../assets/ascii.h"
#include "../assets/background.h"
#include "../assets/sprites.h"

#include "constants.h"
#include "dma.h"
#include "input.h"
#include "memory.h"
#include "objects.h"
#include "register.h"
#include "types.h"

#include <stdint.h>

#define TILE_SIZE 8

Sprite global_sprites[MAX_SPRITE];

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Direction;

void init_snake() {
    uint8_t inital_x[]     = {10, 9, 8};
    uint8_t inital_tiles[] = {1, 0, 0};

    for (int i = 0; i < 3; i++) {
        obj_set_x(&global_sprites[i], inital_x[i] * TILE_SIZE);
        obj_set_y(&global_sprites[i], 10 * TILE_SIZE);
        obj_set_tile(&global_sprites[i], inital_tiles[i]);
        obj_set_priority(&global_sprites[i], 0);
    }

    for (int i = 3; i < MAX_SPRITE; i++) {
        obj_set_priority(&global_sprites[i], 3);
    }
}

void move_snake(Direction direction, uint8_t length) {
    Sprite *head = &global_sprites[0];

    uint8_t new_x  = obj_get_x(head);
    uint16_t new_y = obj_get_y(head);

    switch (direction) {
    case UP:
        obj_set_h_flip(head, 0);
        new_y -= TILE_SIZE;
        break;
    case DOWN:
        obj_set_h_flip(head, 0);
        new_y += TILE_SIZE;
        break;
    case LEFT:
        new_x -= TILE_SIZE;
        obj_set_h_flip(head, 1);
        break;
    case RIGHT:
        new_x += TILE_SIZE;
        obj_set_h_flip(head, 0);
        break;
    }

    for (int i = length - 1; i > 0; i--) {
        obj_set_x(&global_sprites[i], obj_get_x(&global_sprites[i - 1]));
        obj_set_y(&global_sprites[i], obj_get_y(&global_sprites[i - 1]));
    }

    obj_set_x(head, new_x);
    obj_set_y(head, new_y);
}

void irq_handler() {
    //
}

int main() {
    // *REG_IME = 1;
    // *REG_IE  = IRQ_DMA3;

    *REG_DISPCNT = DISP_BG_MODE(0) |
                   DISP_BG0_ENABLE |
                   DISP_OBJ_ENABLE |
                   DISP_OBJ_MAP_1D;

    *REG_BGCNT0 = BG_PRIO(1) |
                  BG_COLOR_MODE(COLOR16) |
                  BG_BASE_CHAR_BLOCK(0) |
                  BG_BASE_SCREEN_BLOCK(8);

    // load palettes
    volatile uint16_t *bg_pal_bf = BG_PAL_BLOCK(0);
    volatile uint16_t *sp_pal_bf = SP_PAL_BLOCK(0);

    for (int i = 0; i < backgroundPalLen / 2; i++) {
        bg_pal_bf[i] = backgroundPal[i];
    }

    for (int i = 0; i < spritesPalLen / 2; i++) {
        sp_pal_bf[i] = spritesPal[i];
    }

    // load bg char block
    volatile uint32_t *bg_char_block = BG_CHAR_BLOCK(0);
    volatile uint32_t *sp_char_block = SP_CHAR_BLOCK(0);

    for (int i = 0; i < backgroundTilesLen / 4; i++) {
        bg_char_block[i] = backgroundTiles[i];
    }

    for (int i = 0; i < spritesTilesLen / 4; i++) {
        sp_char_block[i] = spritesTiles[i];
    }

    // render bg
    volatile uint16_t *bf = BG_SCREEN_BLOCK(8);

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 30; x++) {
            bf[y * 32 + x] = (x + y) % 2 == 0 ? 1 : 0;
        }
    }

    init_snake();

    uint8_t snake_length = 3;
    Direction direction  = RIGHT;

    int stepper = 0;

    while (1) {
        // game logic
        while ((*REG_DISPSTAT & DISP_VBLK_STAT))
            ;

        if (is_key_pressed(KEY_RIGHT) && direction != LEFT) {
            direction = RIGHT;
        } else if (is_key_pressed(KEY_LEFT) && direction != RIGHT) {
            direction = LEFT;
        } else if (is_key_pressed(KEY_UP) && direction != DOWN) {
            direction = UP;
        } else if (is_key_pressed(KEY_DOWN) && direction != UP) {
            direction = DOWN;
        }

        if (stepper == 10) {
            move_snake(direction, snake_length);
            stepper = 0;
        } else {
            stepper += 1;
        }

        // rendering logic
        while (!(*REG_DISPSTAT & DISP_VBLK_STAT)) // wait for vblank
            ;

        uint16_t dma_flags = DMA_ENABLE |
                             DMA_START_TIMING(DMA_START_IMMEDIATE) |
                             DMA_TRANSFER_TYPE(DMA_TRANSFER16);

        uintptr_t oam = (uintptr_t)ADDR_OAM;

        start_dma3((uintptr_t)global_sprites, oam, MAX_SPRITE * OAM_ATTR_COUNT, dma_flags);
    }
}

// int cursor_x = 1;
// int cursor_y = 1;
//
// void print_char(char ch, uint8_t x, uint8_t y, volatile uint16_t *block) {
//     block[y * 32 + x] = ch;
// }
//
// void print_str(char *str, volatile uint16_t *block) {
//     for (int i = 0; str[i] != '\0'; i++) {
//         if (str[i] != '\n') {
//             print_char(str[i], cursor_x, cursor_y, block);
//         }
//
//         if (cursor_x == 28 || str[i] == '\n') {
//             cursor_x = 1;
//             cursor_y += 1;
//         } else {
//             cursor_x += 1;
//         }
//     }
// }
