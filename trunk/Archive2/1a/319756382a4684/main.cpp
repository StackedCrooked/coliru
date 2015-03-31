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

#define _big_endian_loop(it_name, value_name, size_name, ...)\
for (unsigned char * it_name = (unsigned char *)value_name; it_name != (unsigned char *)value_name + size_name; ++it_name)\
{\
    __VA_ARGS__\
}

#define _little_endian_loop(it_name, value_name, size_name, ...)\
unsigned char * it_name = (unsigned char *)value_name + size_name -1;\
do\
{\
    __VA_ARGS__\
}\
while (it-- != (unsigned char *)value_name);

#ifdef __GCC__
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__\
#define _endian_loop(it_name, value_name, size_name, ...) _little_endian_loop(it_name, value_name, size_name, __VA_ARGS__)
#else
#define _endian_loop(it_name, value_name, size_name, ...) _big_endian_loop(it_name, value_name, size_name, __VA_ARGS__)
#endif
#else
#define _endian_loop(it_name, value_name, size_name, ...)\
if (*(uint16_t *)"\0\xff" < 0x100)\
{\
    _big_endian_loop(it_name, value_name, size_name, __VA_ARGS__)\
}\
else\
{\
    _little_endian_loop(it_name, value_name, size_name, __VA_ARGS__)\
}
#endif

void print_le_binary(FILE* out, void *value, size_t size)
{
    static char const * to_bin[] = {C8("")};
    _endian_loop(it, value, size,
    {
        uint8_t slice;
        if (unlikely(CHAR_BIT % 8)) 
        {
            slice = ((*it) >> (8 * (CHAR_BIT/8)));
            fprintf(out, "%s", to_bin[slice]);
        }
        for (char i = CHAR_BIT/8-1; i >= 0; --i)
        {
            slice = ((*it) >> (8 * i));
            fprintf(out, "%s", to_bin[slice]);
        }
    })
    
}

int main() 
{
	uint64_t num = 2582143;
    print_le_binary(stdout, &num, sizeof(num));
	return 0;
}