#include "../assets/ascii.h"

#include "dma.h"
#include "memory.h"
#include "register.h"
#include "types.h"

#include <stdint.h>
#include <sys/types.h>

int cursor_x = 1;
int cursor_y = 1;

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

void irq_handler(void) __attribute__((target("arm")));

void irq_handler() {
    *REG_IE &= ~IE_DMA0;
}

#include <stdint.h>

int main() {
    *REG_IME = 1;
    *REG_IE |= IE_DMA0;

    *REG_DISPCNT = DISP_BG_MODE(0) |
                   DISP_BG0_ENABLE |
                   DISP_OBJ_ENABLE |
                   DISP_OBJ_MAP_1D;

    *REG_BGCNT0 = BG_PRIO(2) |
                  BG_COLOR_MODE(COLOR16) |
                  BG_BASE_CHAR_BLOCK(0) |
                  BG_BASE_SCREEN_BLOCK(8);

    // load palette
    for (int i = 0; i < SharedPalLen / 2; i++) {
        MEM_BG_PAL[i] = SharedPal[i];
    }

    // load bg char block
    volatile uint32_t *bg_char_block = BG_CHAR_BLOCK(0);

    uint16_t dma_flags = DMA_ENABLE |
                         DMA_IRQ |
                         DMA_START_TIMING(DMA_START_IMMEDIATE) |
                         DMA_TRANSFER_TYPE(DMA_TRANSFER32);

    for (int i = 0; i < asciiTilesLen / 4; i++) {
        bg_char_block[i] = asciiTiles[i];
    }

    // clear bg
    volatile uint16_t *bf = BG_SCREEN_BLOCK(8);

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 30; x++) {
            print_char(' ', x, y, bf);
        }
    }

    print_str("Hello World!\n\n", bf);

    while (1)
        ;
}
