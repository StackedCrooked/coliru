#include <stdio.h>
#include <stdint.h>

unsigned char buf[] = {
    0x11, 0x22, 0x33, 0x44,
    0x55, 0x66, 0x77, 0x88,
    0x99, 0xaa, 0xbb, 0xcc
};

#pragma pack(push, 1) // exact fit - no padding
typedef struct mystruct {
    uint16_t var1;
    uint16_t var2;
    uint32_t var3;
    uint32_t var4;
} something;
#pragma pack(pop) //back to whatever the previous packing mode was

static uint16_t swap16(uint16_t val)
{
    return ((val >> 8) & 0xFF) | ((val << 8) & 0xFF00);
}

static uint32_t swap32(uint32_t val)
{
    uint16_t v1 = swap16((uint16_t) val);
    uint16_t v2 = swap16((uint16_t) (val >> 16));
    return (v1 << 16) | (v2);
}

int main(void)
{
    printf("sizeof buf: %zu %zu \n", sizeof(buf), sizeof(something));
    something *st = (something*)&(buf[0]);

    #define pr(a) printf(#a" %x\n", a)

#if __BYTE_ORDER == __LITTLE_ENDIAN 
    st->var1 = swap16(st->var1);
    st->var2 = swap16(st->var2);
    st->var3 = swap32(st->var3);
    st->var4 = swap32(st->var4);
#endif

    pr(st->var1);
    pr(st->var2);
    pr(st->var3);
    pr(st->var4);

    return(0);
}