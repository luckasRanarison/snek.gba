#ifndef REGISTER_H
#define REGISTER_H

#include "constants.h"

/*-----------------------------------------------------*/
/*         DISPCNT (0x04000000): read/write            */
/*-----------------------------------------------------*/
#define REG_DISPCNT ((volatile uint16_t *)(ADDR_IO_REG + 0x000))

#define BG_MODE(mode)       mode
#define FRM_BUFF(flag)      (flag << 4)
#define HBLK_OBJ_PROC(flag) (flag << 5)
#define OBJ_MAP_2D          (0 << 6)
#define OBJ_MAP_1D          (1 << 6)
#define FORCED_BLK(flag)    (flag << 7)
#define BG0(flag)           (flag << 8)
#define BG1(flag)           (flag << 9)
#define BG2(flag)           (flag << 10)
#define BG3(flag)           (flag << 11)
#define OBJ(flag)           (flag << 12)
#define WIN0(flag)          (flag << 13)
#define WIN1(flag)          (flag << 14)
#define OBJ_WIN(flag)       (flag << 15)

/*-----------------------------------------------------*/
/*          DISPSTAT (0x04000004): read/write          */
/*-----------------------------------------------------*/
#define REG_DISPSTAT ((volatile uint16_t *)(ADDR_IO_REG + 0x004))

#define VBLK_STAT   (0 << 0)
#define HBLK_STAT   (1 << 1)
#define VCOUNT_EVAL (1 << 2)
#define VBLK_IRQ    (1 << 3)
#define HBLK_IRQ    (1 << 4)
#define VCOUNT_IRQ  (1 << 5)

/*-----------------------------------------------------*/
/*              VCOUNT (0x04000006): read              */
/*-----------------------------------------------------*/
#define REG_VCOUNT ((volatile uint16_t *)(ADDR_IO_REG + 0x006))

/*-----------------------------------------------------*/
/*                  BGCNT: read/write                  */
/*-----------------------------------------------------*/
#define REG_BGCNT0 ((volatile uint16_t *)(ADDR_IO_REG + 0x008))
#define REG_BGCNT1 ((volatile uint16_t *)(ADDR_IO_REG + 0x00A))
#define REG_BGCNT2 ((volatile uint16_t *)(ADDR_IO_REG + 0x00C))
#define REG_BGCNT3 ((volatile uint16_t *)(ADDR_IO_REG + 0x00E))

#define BG_PRIO(prio)             prio
#define BASE_BG_CHAR_BLOCK(block) (block << 2)
#define BG_MOSAIC(flag)           (flag << 6)
#define COLOR_MODE(flag)          (flag << 7)
#define BASE_SCREEN_BLOCK(block)  (block << 8)
#define AREA_OVFL_PROC(flag)      (flag << 13)
#define SCREEN_SIZE(size)         (size << 14)

/*-----------------------------------------------------*/
/*                        DMA : write                  */
/*-----------------------------------------------------*/
#define REG_DMA0SAD_L ((volatile uint16_t *)(ADDR_IO_REG + 0x0B0))
#define REG_DMA0SAD_H ((volatile uint16_t *)(ADDR_IO_REG + 0x0B2))
#define REG_DMA0DAD_L ((volatile uint16_t *)(ADDR_IO_REG + 0x0B4))
#define REG_DMA0DAD_H ((volatile uint16_t *)(ADDR_IO_REG + 0x0B6))
#define REG_DMA0CNT_L ((volatile uint16_t *)(ADDR_IO_REG + 0x0B8))
#define REG_DMA0CNT_H ((volatile uint16_t *)(ADDR_IO_REG + 0x0BA))

#define DMA_REPEAT(flag)        (flag << 9)
#define DMA_TRANSFER_TYPE(flag) (flag << 10)
#define DMA_START_TIMING(flag)  (flag << 12)
#define DMA_IRQ(flag)           (flag << 14)
#define DMA_ENABLE(flag)        (flag << 15)

/*-----------------------------------------------------*/
/*              KEYINPUT (0x04000130): read            */
/*-----------------------------------------------------*/
#define REG_KEYINPUT ((volatile uint16_t *)(ADDR_IO_REG + 0x130))

#endif // !REGISTER_H
