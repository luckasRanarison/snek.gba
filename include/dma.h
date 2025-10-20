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

typedef enum {
    DMA_INCREMENT_ADDR,
    DMA_DECREMENT_ADDR,
    DMA_FIXED_ADDR,
} DMAAddressCtrl;

inline void start_dma0(uint32_t src_addr, uint32_t dst_addr, uint16_t length, uint16_t flags) {
    *REG_DMA0SAD   = src_addr;
    *REG_DMA0DAD   = dst_addr;
    *REG_DMA0CNT_L = length;
    *REG_DMA0CNT_H = flags;
}

inline void start_dma1(uint32_t src_addr, uint32_t dst_addr, uint16_t length, uint16_t flags) {
    *REG_DMA1SAD   = src_addr;
    *REG_DMA1DAD   = dst_addr;
    *REG_DMA1CNT_L = length;
    *REG_DMA1CNT_H = flags;
}

inline void start_dma2(uint32_t src_addr, uint32_t dst_addr, uint16_t length, uint16_t flags) {
    *REG_DMA2SAD   = src_addr;
    *REG_DMA2DAD   = dst_addr;
    *REG_DMA2CNT_L = length;
    *REG_DMA2CNT_H = flags;
}

inline void start_dma3(uint32_t src_addr, uint32_t dst_addr, uint16_t length, uint16_t flags) {
    *REG_DMA3SAD   = src_addr;
    *REG_DMA3DAD   = dst_addr;
    *REG_DMA3CNT_L = length;
    *REG_DMA3CNT_H = flags;
}

#endif
