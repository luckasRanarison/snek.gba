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

#define TILE_SIZE         8
#define INITIAL_LENGTH    3
#define INITIAL_DIRECTION RIGHT

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Direction;

typedef struct {
    uint8_t snake_length;
    Direction direction;
    int stepper;
    Sprite sprites[MAX_SPRITE];
} GameState;

void init_game(GameState *state) {
    uint8_t inital_x[] = {10, 9, 8};
    uint8_t inital_tiles[] = {1, 0, 0};

    for (int i = 0; i < 3; i++) {
        obj_set_x(&state->sprites[i], inital_x[i] * TILE_SIZE);
        obj_set_y(&state->sprites[i], 10 * TILE_SIZE);
        obj_set_tile(&state->sprites[i], inital_tiles[i]);
        obj_set_priority(&state->sprites[i], 0);
    }

    for (int i = 3; i < MAX_SPRITE; i++) {
        obj_set_priority(&state->sprites[i], 3);
    }

    state->stepper = 0;
    state->direction = INITIAL_DIRECTION;
    state->snake_length = INITIAL_LENGTH;
}

void handle_input(GameState *state) {
    if (is_key_pressed(KEY_RIGHT) && state->direction != LEFT) {
        state->direction = RIGHT;
    } else if (is_key_pressed(KEY_LEFT) && state->direction != RIGHT) {
        state->direction = LEFT;
    } else if (is_key_pressed(KEY_UP) && state->direction != DOWN) {
        state->direction = UP;
    } else if (is_key_pressed(KEY_DOWN) && state->direction != UP) {
        state->direction = DOWN;
    }
}

void move_snake(GameState *state) {
    Sprite *head = &state->sprites[0];

    uint8_t new_x = obj_get_x(head);
    uint16_t new_y = obj_get_y(head);

    switch (state->direction) {
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

    for (int i = state->snake_length - 1; i > 0; i--) {
        obj_set_x(&state->sprites[i], obj_get_x(&state->sprites[i - 1]));
        obj_set_y(&state->sprites[i], obj_get_y(&state->sprites[i - 1]));
    }

    obj_set_x(head, new_x);
    obj_set_y(head, new_y);
}

void update_sprite(GameState *state) {
    uint16_t dma_flags = DMA_ENABLE |
                         DMA_START_TIMING(DMA_START_IMMEDIATE) |
                         DMA_TRANSFER_TYPE(DMA_TRANSFER16);

    uintptr_t oam = (uintptr_t)ADDR_OAM;

    start_dma3((uintptr_t)state->sprites, oam, MAX_SPRITE * OAM_ATTR_COUNT, dma_flags);
}

void irq_handler() {
    //
}

int main() {
    GameState state;

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

    init_game(&state);

    while (1) {
        // game logic
        while ((*REG_DISPSTAT & DISP_VBLK_STAT))
            ;

        handle_input(&state);

        if (state.stepper == 10) {
            move_snake(&state);
            state.stepper = 0;
        } else {
            state.stepper += 1;
        }

        // rendering logic
        while (!(*REG_DISPSTAT & DISP_VBLK_STAT)) // wait for vblank
            ;

        update_sprite(&state);
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
