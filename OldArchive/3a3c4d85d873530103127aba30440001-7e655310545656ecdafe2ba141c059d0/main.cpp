#include <stdio.h>

#define DECR_(t, x) ({ t y = (x); --y; y; })
#define DECR(x) _Generic((x), \
    int: DECR_(int, (x)), \
    const int: DECR_(int, (x)), \
    long: DECR_(long, (x)), \
    const long: DECR_(long, (x)), \
    unsigned int: DECR_(unsigned int, (x)), \
    const unsigned int: DECR_(unsigned int, (x)), \
    long long: DECR_(long long, (x)), \
    const long long: DECR_(long long, (x)))

int main(void) {
    {
        int value = 5;
        printf("%d\n", DECR(value));
    }
    {
        const int value = 5;
        printf("%d\n", DECR(value));
    }
    {
        const long long value = 5LL;
        printf("%lld\n", DECR(value));
    }
    return 0;
}
