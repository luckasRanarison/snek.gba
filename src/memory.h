#ifndef MEMORY_H
#define MEMORY_H

#define MEM_VRAM8   ((volatile uint8_t *)(ADDR_VRAM))
#define MEM_VRAM16  ((volatile uint16_t *)(ADDR_VRAM))
#define MEM_VRAM32  ((volatile uint32_t *)(ADDR_VRAM))
#define MEM_BG_PAL  ((volatile uint16_t *)(ADDR_BG_PAL))
#define MEM_OBJ_PAL ((volatile uint16_t *)(ADDR_OBJ_PAL))

#define BG_CHAR_BLOCK(block)   ((volatile uint32_t *)(ADDR_VRAM + block * 0x4000))
#define BG_SCREEN_BLOCK(block) ((volatile uint16_t *)(ADDR_VRAM + block * 0x800))

#endif // !MEMORY_H
