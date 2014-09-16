#include <stdio.h>

#define printf_dec_format(x) _Generic((x), \
    char: "%c", \
    signed int: "%d", \
    unsigned int: "%u", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s")
 
#define print(x) printf(printf_dec_format(x), x)
#define println(x) printf(printf_dec_format(x), x), printf("\n");

int main() {
    {
        int x = 5;
        println(x);
    }
    {
        int x = 6;
        println(x);
    }
}