#ifndef BITFLAGS
#define BITFLAGS

#define SET_BITS(dst, mask, val, shift) \
    dst = (dst & ~(mask << shift)) | (val << shift)

#define GET_BITS(dst, mask, shift) \
    ((dst >> shift) & mask)

#endif // !BITFLAGS
