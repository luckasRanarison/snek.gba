#ifndef DMA_H
#define DMA_H

#include "register.h"

#include <stdint.h>

typedef enum {
    DMA_TRANSFER16,
    DMA_TRANSFER32,
} DMATransferType;

typedef enum {
    DMA_START_IMMEDIATE,
    DMA_START_VBLANK,
    DMA_START_HBLANK,
} DMAStartTiming;

inline void start_dma0(uint32_t src_addr, uint32_t dst_addr, uint16_t length, uint16_t flags) {
    *REG_DMA0SAD   = src_addr;
    *REG_DMA0DAD   = dst_addr;
    *REG_DMA0CNT_H = flags;
    *REG_DMA0CNT_L = length;
}

#endif
