#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int fun(int x) { return x + 2; }

int main(void)
{
    int (*fptr)(int) = fun; // the address is stored here
    intptr_t x = (intptr_t)fptr; // its integer form here

    printf("The address is %p (as pointer) "
           "or %#" PRIxPTR " (as integer)\n", fptr, x);

    // now call them
    printf("Calling via ptr: %d, via int: %d\n",
           fptr(9), ((int(*)(int))x)(8));
}
