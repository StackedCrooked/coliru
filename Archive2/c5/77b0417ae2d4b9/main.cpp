#include <limits>       // std::numeric_limits
#include <algorithm>    // std::reverse

namespace cppx {
    using std::numeric_limits;
    using std::reverse;
    
    typedef numeric_limits<long>    Long_info;
    int const long_digits   = Long_info::max_digits10;
    int const long_bufsize  = long_digits + 2;
    
    inline void unsigned_to_decimal( unsigned long number, char* buffer )
    {
        if( number == 0 )
        {
            *buffer++ = '0';
        }
        else
        {
            char* p_first = buffer;
            while( number != 0 )
            {
                *buffer++ = '0' + number % 10;
                number /= 10;
            }
            reverse( p_first, buffer );
        }
        *buffer = '\0';
    }
    
    inline auto decimal_from_unsigned( unsigned long number, char* buffer )
    -> char const*
    {
        unsigned_to_decimal( number, buffer );
        return buffer;
    }
    
    inline void to_decimal( long number, char* buffer )
    {
        if( number < 0 )
        {
            buffer[0] = '-';
            unsigned_to_decimal( -number, buffer + 1 );
        }
        else
        {
            unsigned_to_decimal( number, buffer );
        }
    }
    
    __attribute__((__noinline__))
    auto decimal_from( long number, char* buffer )
    -> char const*
    {
        to_decimal( number, buffer );
        return buffer;
    }
}  // namespace cppx

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

__attribute__((__noinline__))
void int_to_string(int32_t value, char* buffer) {
    if (value == INT_MIN) {
        strcpy(buffer, "-2147483648");
        return;
    }
    if (value < 0) {
        value = -value;
        *buffer++ = '-';
    }
    if (value < 10) {
        buffer[0] = '0' + value;
        buffer[1] = '\0';
        return;
    }
    
    char* pstart = buffer;
    
    // INT_MAX = 2147483647
    int bufneed;
    
    if (value >= 1000000000) {
        if (value >= 2000000000) {
            *pstart++ = '2';
            value -= 2000000000;
            
            if (value >= 100000000) {
                *pstart++ = '1';
                value -= 100000000;
            } else {
                *pstart++ = '0';
            }
            bufneed = 8;
        } else {
            *pstart++ = '1';
            bufneed = 9;
        }
    } else {
        // 123456789
        if (value >= 10000) {
            if (value >= 1000000) {
                if (value >= 100000000) {
                    bufneed = 9;
                } else if (value >= 10000000) {
                    bufneed = 8;
                } else {
                    bufneed = 7;
                }
            } else if (value >= 100000) {
                bufneed = 6;
            } else {
                bufneed = 5;
            }
        } else if (value >= 100) {
            if (value >= 1000) {
                bufneed = 4;
            } else {
                bufneed = 3;
            }
        } else if (value >= 10) {
            bufneed = 2;
        } else {
            // __builtin_unreachable()
            abort();
        }
    }
    char* pend = pstart + bufneed;
    *pend-- = '\0';
    while (value > 0) {
        *pend-- = '0' + value % 10;
        value /= 10;
    }
    while (pend >= pstart) {
        *pend-- = '0';
    }
}

/*
 **  LTOA.C
 **
 **  Converts a long integer to a string.
 **
 **  Copyright 1988-90 by Robert B. Stout dba MicroFirm
 **
 **  Released to public domain, 1991
 **
 **  Parameters: 1 - number to be converted
 **              2 - buffer in which to build the converted string
 **              3 - number base to use for conversion
 **
 **  Returns:  A character pointer to the converted string if
 **            successful, a NULL pointer if the number base specified
 **            is out of range.
 */

#include <stdlib.h>
#include <string.h>

#define BUFSIZE (sizeof(long) * 8 + 1)

__attribute__((__noinline__))
char *ltoa(long N, char *str, int base)
{
    register int i = 2;
    long uarg;
    char *tail, *head = str, buf[BUFSIZE];
    
    if (36 < base || 2 > base)
        base = 10;                    /* can only use 0-9, A-Z        */
    tail = &buf[BUFSIZE - 1];           /* last character position      */
    *tail-- = '\0';
    
    if (10 == base && N < 0L)
    {
        *head++ = '-';
        uarg    = -N;
    }
    else  uarg = N;
    
    if (uarg)
    {
        for (i = 1; uarg; ++i)
        {
            register ldiv_t r;
            
            r       = ldiv(uarg, base);
            *tail-- = (char)(r.rem + ((9L < r.rem) ?
                                      ('A' - 10L) : '0'));
            uarg    = r.quot;
        }
    }
    else  *tail-- = '0';
    
    memcpy(head, ++tail, i);
    return str;
}

#include <assert.h>

#define TEST_COUNT 1000000

__attribute__((__noinline__))
void test_decimal_from() {
    char buf[32];
    for (int i=0; i<TEST_COUNT; ++i) {
#define TEST(NUM) cppx::decimal_from(NUM, buf); assert(strcmp(buf, #NUM) == 0)
        TEST(1);
        TEST(-1);
        TEST(483600);
        TEST(-483600);
        TEST(1000483600);
        TEST(-1000483600);
        TEST(1100483600);
        TEST(-1100483600);
        TEST(1111483600);
        TEST(-1111483600);
        TEST(2000483600);
        TEST(-2000483600);
        TEST(2100483600);
        TEST(-2100483600);
        TEST(2110483600);
        TEST(-2110483600);
        
        TEST(0);
        TEST(100000000);
        TEST(-100000000);
        TEST(-2147483648); // INT_MIN
        TEST(-2147483647); // INT_MIN + 1
        TEST(2147483647);  // INT_MAX
        TEST(2147483646);  // INT_MAX - 1
#undef TEST
    }
}

__attribute__((noinline))
void test_int_to_string() {
    char buf[32];
    for (int i=0; i<TEST_COUNT; ++i) {
#define TEST(NUM) int_to_string(NUM, buf); assert(strcmp(buf, #NUM) == 0)
        TEST(1);
        TEST(-1);
        TEST(483600);
        TEST(-483600);
        TEST(1000483600);
        TEST(-1000483600);
        TEST(1100483600);
        TEST(-1100483600);
        TEST(1111483600);
        TEST(-1111483600);
        TEST(2000483600);
        TEST(-2000483600);
        TEST(2100483600);
        TEST(-2100483600);
        TEST(2110483600);
        TEST(-2110483600);
        
        TEST(0);
        TEST(100000000);
        TEST(-100000000);
        TEST(-2147483648); // INT_MIN
        TEST(-2147483647); // INT_MIN + 1
        TEST(2147483647);  // INT_MAX
        TEST(2147483646);  // INT_MAX - 1
#undef TEST
    }
}

__attribute__((noinline))
void test_sprintf() {
    char buf[32];
    for (int i=0; i<TEST_COUNT; ++i) {
#define TEST(NUM) sprintf(buf, "%d", NUM); assert(strcmp(buf, #NUM) == 0)
        TEST(1);
        TEST(-1);
        TEST(483600);
        TEST(-483600);
        TEST(1000483600);
        TEST(-1000483600);
        TEST(1100483600);
        TEST(-1100483600);
        TEST(1111483600);
        TEST(-1111483600);
        TEST(2000483600);
        TEST(-2000483600);
        TEST(2100483600);
        TEST(-2100483600);
        TEST(2110483600);
        TEST(-2110483600);
        
        TEST(0);
        TEST(100000000);
        TEST(-100000000);
        TEST(-2147483648); // INT_MIN
        TEST(-2147483647); // INT_MIN + 1
        TEST(2147483647);  // INT_MAX
        TEST(2147483646);  // INT_MAX - 1
#undef TEST
    }
}

__attribute__((noinline))
void test_ltoa() {
    char buf[32];
    for (int i=0; i<TEST_COUNT; ++i) {
#define TEST(NUM) ltoa(NUM, buf, 10); assert(strcmp(buf, #NUM) == 0)
        TEST(1);
        TEST(-1);
        TEST(483600);
        TEST(-483600);
        TEST(1000483600);
        TEST(-1000483600);
        TEST(1100483600);
        TEST(-1100483600);
        TEST(1111483600);
        TEST(-1111483600);
        TEST(2000483600);
        TEST(-2000483600);
        TEST(2100483600);
        TEST(-2100483600);
        TEST(2110483600);
        TEST(-2110483600);
        
        TEST(0);
        TEST(100000000);
        TEST(-100000000);
        TEST(-2147483648); // INT_MIN
        TEST(-2147483647); // INT_MIN + 1
        TEST(2147483647);  // INT_MAX
        TEST(2147483646);  // INT_MAX - 1
#undef TEST
    }
}

#include <time.h>
#include <stdio.h>

int main() {
    {
        clock_t now = clock();
        test_decimal_from();
        clock_t spent = clock() - now;
        printf("decimal_from:  %ld\n", spent);
    }
    {
        clock_t now = clock();
        test_int_to_string();
        clock_t spent = clock() - now;
        printf("int_to_string: %ld\n", spent);
    }
    {
        clock_t now = clock();
        test_sprintf();
        clock_t spent = clock() - now;
        printf("sprintf:       %ld\n", spent);
    }
    {
        clock_t now = clock();
        test_ltoa();
        clock_t spent = clock() - now;
        printf("ltoa:          %ld\n", spent);
    }
}
