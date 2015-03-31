#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

#define C2(s) s"00", s"01", s"10", s"11"
#define C4(s) C2(s"00"), C2(s"01"), C2(s"10"), C2(s"11")
#define C6(s) C4(s"00"), C4(s"01"), C4(s"10"), C4(s"11")
#define C8(s) C6(s"00"), C6(s"01"), C6(s"10"), C6(s"11")

#ifdef __GNUC__
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define unlikely(x)     (x)
#endif

void print_binary(FILE* out, void *value, size_t size)
{
    static char const * to_bin[] = {C8("")};
    for (size_t it = 0; it < size; ++it)
    {
        unsigned char *p = (unsigned char *)value + it;
        uint8_t slice;
        for (size_t i = 0; i < CHAR_BIT / 8; ++i)
        {
            slice = ((*p) >> (8 * i));
            fprintf(out, "%s", to_bin[slice]);
        }
        if (unlikely(CHAR_BIT % 8)) 
        {
            slice = ((*p) >> (8 * (CHAR_BIT / 8)));
            fprintf(out, "%s", to_bin[slice]);
        }
    }
}

int main() 
{
	uint64_t num = -1;
    print_binary(stdout, &num, sizeof(num));
	return 0;
}