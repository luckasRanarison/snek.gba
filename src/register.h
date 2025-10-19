#ifndef REGISTER_H
#define REGISTER_H

#include "constants.h"

/*-----------------------------------------------------*/
/*         DISPCNT (0x04000000): read/write            */
/*-----------------------------------------------------*/
#define REG_DISPCNT ((volatile uint16_t *)(ADDR_IO_REG + 0x000))

#define DISP_BG_MODE(mode)  mode
#define DISP_FRM_BUFF       (1 << 4)
#define DISP_HBLK_OBJ_PROC  (1 << 5)
#define DISP_OBJ_MAP_2D     (0 << 6)
#define DISP_OBJ_MAP_1D     (1 << 6)
#define DISP_FORCED_BLK     (1 << 7)
#define DISP_BG0_ENABLE     (1 << 8)
#define DISP_BG1_ENABLE     (1 << 9)
#define DISP_BG2_ENABLE     (1 << 10)
#define DISP_BG3_ENABLE     (1 << 11)
#define DISP_OBJ_ENABLE     (1 << 12)
#define DISP_WIN0_ENABLE    (1 << 13)
#define DISP_WIN1_ENABLE    (1 << 14)
#define DISP_OBJ_WIN_ENABLE (1 << 15)

/*-----------------------------------------------------*/
/*          DISPSTAT (0x04000004): read/write          */
/*-----------------------------------------------------*/
#define REG_DISPSTAT ((volatile uint16_t *)(ADDR_IO_REG + 0x004))

#define DISP_VBLK_STAT   (0 << 0)
#define DISP_HBLK_STAT   (1 << 1)
#define DISP_VCOUNT_EVAL (1 << 2)
#define DISP_VBLK_IRQ    (1 << 3)
#define DISP_HBLK_IRQ    (1 << 4)
#define DISP_VCOUNT_IRQ  (1 << 5)

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

#define BG_PRIO(prio)               prio
#define BG_BASE_CHAR_BLOCK(block)   (block << 2)
#define BG_MOSAIC                   (1 << 6)
#define BG_COLOR_MODE(mode)         (mode << 7)
#define BG_BASE_SCREEN_BLOCK(block) (block << 8)
#define BG_AREA_OVFL_PROC           (1 << 13)
#define BG_SCREEN_SIZE(size)        (size << 14)

/*-----------------------------------------------------*/
/*                   DMA : read/write                  */
/*-----------------------------------------------------*/
#define REG_DMA0SAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0B0))
#define REG_DMA0DAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0B4))
#define REG_DMA0CNT_L ((volatile uint16_t *)(ADDR_IO_REG + 0x0B8))
#define REG_DMA0CNT_H ((volatile uint16_t *)(ADDR_IO_REG + 0x0BA))

#define REG_DMA1SAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0BC))
#define REG_DMA1DAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0C0))
#define REG_DMA1CNT_L ((volatile uint16_t *)(ADDR_IO_REG + 0x0C4))
#define REG_DMA1CNT_H ((volatile uint16_t *)(ADDR_IO_REG + 0x0C6))

#define REG_DMA2SAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0C8))
#define REG_DMA2DAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0CC))
#define REG_DMA2CNT_L ((volatile uint16_t *)(ADDR_IO_REG + 0x0D0))
#define REG_DMA2CNT_H ((volatile uint16_t *)(ADDR_IO_REG + 0x0D2))

#define REG_DMA3SAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0D4))
#define REG_DMA3DAD   ((volatile uint32_t *)(ADDR_IO_REG + 0x0D8))
#define REG_DMA3CNT_L ((volatile uint16_t *)(ADDR_IO_REG + 0x0DC))
#define REG_DMA3CNT_H ((volatile uint16_t *)(ADDR_IO_REG + 0x0DE))

#define DMA_DST_ADDR(type)      (type << 5)
#define DMA_SRC_ADDR(type)      (type << 7)
#define DMA_REPEAT              (1 << 9)
#define DMA_TRANSFER_TYPE(type) (type << 10)
#define DMA_START_TIMING(type)  (type << 12)
#define DMA_IRQ                 (1 << 14)
#define DMA_ENABLE              (1 << 15)

/*-----------------------------------------------------*/
/*              KEYINPUT (0x04000130): read            */
/*-----------------------------------------------------*/
#define REG_KEYINPUT ((volatile uint16_t *)(ADDR_IO_REG + 0x130))

/*-----------------------------------------------------*/
/*             IE (0x04000200): read / write           */
/*-----------------------------------------------------*/
#define REG_IE ((volatile uint16_t *)(ADDR_IO_REG + 0x200))

/*-----------------------------------------------------*/
/*             IF (0x04000202): read / write           */
/*-----------------------------------------------------*/
#define REG_IF ((volatile uint16_t *)(ADDR_IO_REG + 0x202))

#define IRQ_VBLANK       (1 << 0)
#define IRQ_HBLANK       (1 << 1)
#define IRQ_VCOUNT_MATCH (1 << 2)
#define IRQ_TIMER0       (1 << 3)
#define IRQ_TIMER1       (1 << 4)
#define IRQ_TIMER2       (1 << 5)
#define IRQ_TIMER3       (1 << 6)
#define IRQ_SERIAL       (1 << 7)
#define IRQ_DMA0         (1 << 8)
#define IRQ_DMA1         (1 << 9)
#define IRQ_DMA2         (1 << 10)
#define IRQ_DMA3         (1 << 11)
#define IRQ_KEYPAD       (1 << 12)
#define IRQ_GAMEPAK      (1 << 13)

/*-----------------------------------------------------*/
/*            IME (0x04000208): read / write           */
/*-----------------------------------------------------*/
#define REG_IME ((volatile uint16_t *)(ADDR_IO_REG + 0x208))

#endif // !REGISTER_H
