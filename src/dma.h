#ifndef DMA_H
#define DMA_H

typedef enum {
    DMA16,
    DMA32,
} DMATransferType;

typedef enum {
    DMA_START_IMMEDIATE,
    DMA_START_VBLANK,
    DMA_START_HBLANK,
} DMAStartTiming;

#endif
