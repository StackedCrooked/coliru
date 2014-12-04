#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
 
int main(void)
{
    int *p = aligned_alloc(16, 32);
    
    printf("%2zu\n", _Alignof(unsigned char));
    printf("%2zu\n", _Alignof(int));
    printf("%2zu\n", _Alignof(double));
    printf("%2zu\n", _Alignof(long double));
    printf("%2zu\n", _Alignof(long double _Complex));
    printf("%2zu\n", _Alignof(max_align_t));
 
    /* The compiler inserts padding bytes between members and after the last member */
    /* to ensure that all members are aligned properly in an array of the struct.   */
    struct s {
        char c;
        /* 7 bytes of padding here */
        double d;   /* greatest alignment requirement is alignment of struct */
        int i;
        /* 4 bytes of padding here */
    } ss[2];
    printf("sizeof(s)   = %2zu\n", sizeof(struct s));
    printf("_Alignof(s) = %2zu\n", _Alignof(struct s));
    printf("&ss[0].d    = %p\n", (void*)&ss[0].d);   /* 8-byte alignment */
    printf("&ss[1].d    = %p\n", (void*)&ss[1].d);
 
    /* Make an alignment stricter. */
    int a;
    printf("&a          = %p\n", (void*)&a);   /* 4-byte alignment  */
    _Alignas(16) int b;
    printf("&b          = %p\n", (void*)&b);   /* 16-byte alignment */
 
    return 0;
}