#ifndef MEMORY_H
#define MEMORY_H

#define BG_CHAR_BLOCK(block)   ((volatile uint32_t *)(ADDR_VRAM + block * 0x4000))
#define BG_SCREEN_BLOCK(block) ((volatile uint16_t *)(ADDR_VRAM + block * 0x800))
#define BG_PAL_BLOCK(block)    ((volatile uint16_t *)(ADDR_BG_PAL + block * 0x10))
#define SP_PAL_BLOCK(block)    ((volatile uint16_t *)(ADDR_SP_PAL + block * 0x10))
#define SP_CHAR_BLOCK(bg_mode) ((volatile uint32_t *)(ADDR_VRAM + (bg_mode <= 2 ? 0x10000 : 0x14000)))

#endif // !MEMORY_H
