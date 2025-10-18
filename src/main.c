#include "../assets/ascii.h"
#include "memory.h"
#include "register.h"
#include "types.h"

#include <stdint.h>
#include <sys/types.h>

int cursor_x = 1;
int cursor_y = 1;

void irq_handler() {
    // TODO
}

void print_char(char ch, uint8_t x, uint8_t y, volatile uint16_t *block) {
    block[y * 32 + x] = ch;
}

void print_str(char *str, volatile uint16_t *block) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\n') {
            print_char(str[i], cursor_x, cursor_y, block);
        }

        if (cursor_x == 28 || str[i] == '\n') {
            cursor_x = 1;
            cursor_y += 1;
        } else {
            cursor_x += 1;
        }
    }
}

int main() {
    *REG_DISPCNT = BG_MODE(0) |
                   BG0(1) |
                   OBJ(1) |
                   OBJ_MAP_1D;

    *REG_BGCNT0 = BG_PRIO(2) |
                  COLOR_MODE(COLOR16) |
                  BASE_BG_CHAR_BLOCK(0) |
                  BASE_SCREEN_BLOCK(8);

    // load palette
    for (int i = 0; i < SharedPalLen / 2; i++) {
        MEM_BG_PAL[i] = SharedPal[i];
    }

    // load bg char block
    volatile uint32_t *bg_char_block = BG_CHAR_BLOCK(0);

    for (int i = 0; i < asciiTilesLen / 4; i++) {
        bg_char_block[i] = asciiTiles[i];
    }

    // clear bg
    volatile uint16_t *bg_screen_block = BG_SCREEN_BLOCK(8);

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 30; x++) {
            print_char(' ', x, y, bg_screen_block);
        }
    }

    print_str("Hello world!\n\nThis is quite a long text,\n\nso it should line break", bg_screen_block);

    while (1)
        ;
}
