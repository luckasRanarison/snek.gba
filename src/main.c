#include "../assets/ascii.h"

#include "dma.h"
#include "memory.h"
#include "register.h"
#include "types.h"

#include <stdint.h>

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

void irq_handler() {
    *REG_IF = IRQ_DMA3;
}

int main() {
    *REG_IME = 1;
    *REG_IE  = IRQ_DMA3;

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

    start_dma3((uintptr_t)asciiTiles, 0x06000000, asciiTilesLen / 4, dma_flags);

    // this is unreachable

    while (1) {
        // if ((*REG_DMA3CNT_H & DMA_ENABLE) == 0) {
        // clear bg
        volatile uint16_t *bf = BG_SCREEN_BLOCK(8);

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 30; x++) {
                print_char(' ', x, y, bf);
            }
        }

        print_str("DMA complete!\n\n", bf);
        // }
    }
}
