#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
 
int main(void)
{
    // simple usage
    char source[] = "once upon a midnight dreary...", dest[4];
    memcpy(dest, source, sizeof dest);
    for(size_t n = 0; n < sizeof dest; ++n)
        putchar(dest[n]);
 
    // reinterpreting data
    double d = 0.1;
//    int64_t n = *(int64_t*)(&d); // strict aliasing violation
    int64_t n;
    memcpy(&n, &d, sizeof d); // OK
 
    printf("\n%a is %" PRIx64 " as an int64_t\n", d, n);
}