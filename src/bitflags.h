#ifndef BITFLAGS
#define BITFLAGS

#define SET_BITS(reg, mask, val) \
    reg = (reg & ~(mask)) | val

#endif // !BITFLAGS
