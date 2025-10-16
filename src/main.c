#include <stdint.h>

#define ADDR_IO   0x04000000
#define ADDR_VRAM 0x06000000

#define REG16(addr) ((volatile uint16_t *)(addr))
#define REG_DISPCNT REG16(ADDR_IO)

#define MEM_VRAM ((volatile uint16_t *)(ADDR_VRAM))

#define LCD_WIDTH  240
#define LCD_HEIGHT 160

int main() {
    // set BG 2 flag and switch to mode 3
    *REG_DISPCNT = (1 << 10) | 3;

    uint16_t blue = 0x7C00;

    for (int y = 0; y < LCD_HEIGHT; y++) {
        for (int x = 0; x < LCD_WIDTH; x++) {
            MEM_VRAM[y * LCD_WIDTH + x] = blue;
        }
    }

    while (1)
        ;
}
