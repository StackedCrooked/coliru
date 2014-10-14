#include <stdio.h>
#include <stdint.h>
 
int main(void)
{   
    printf("PTRDIFF_MIN    = %+ld\n", 0);
    printf("PTRDIFF_MAX    = %+ld\n", PTRDIFF_MAX);
    printf("SIZE_MAX       = %lu\n",  SIZE_MAX);
    printf("SIG_ATOMIC_MIN = %+d\n",  SIG_ATOMIC_MIN);
    printf("SIG_ATOMIC_MAX = %+d\n",  SIG_ATOMIC_MAX);
    printf("WCHAR_MIN      = %+d\n",  WCHAR_MIN);
    printf("WCHAR_MAX      = %+d\n",  WCHAR_MAX);
    printf("WINT_MIN       = %u\n",   WINT_MIN);
    printf("WINT_MAX       = %u\n",   WINT_MAX);
}