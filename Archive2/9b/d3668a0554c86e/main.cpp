#include <stdint.h>
#include <stdio.h>

void dump(const char* did_what, bool x, const uint8_t* xmem)
{
    printf("did what to 'x'  : %s\n", did_what);
    printf("memory of 'x'    : 0x%02x\n", *xmem);
    printf("is 'x' == 'true' : %s\n", x ? "yes" : "no");
    printf("\n");
}

int main()
{
    bool x;
    uint8_t* xmem = reinterpret_cast<uint8_t*>(&x);

    x = false;
    dump("x = false", x, xmem);

    x = true;
    dump("x = true", x, xmem);
    
    *xmem = 0;
    dump("*xmem = 0", x, xmem);

    *xmem = 1;
    dump("*xmem = 1", x, xmem);

    *xmem = 2;
    dump("*xmem = 2", x, xmem);
     
    return 0;
}