
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>


#if   defined(__i386__)
static unsigned long long cpucycles( void )
{
  unsigned long long result;
  __asm__ __volatile__
  ( 
    ".byte 15;.byte 49" 
    : "=A" ( result ) 
  );
  return result;
}
#elif defined(__x86_64__)
static unsigned long long cpucycles( void )
{
  unsigned long long result;
  __asm__ __volatile__
  ( 
    ".byte 15;.byte 49\n"
    "shlq $32,%%rdx\n"
    "orq %%rdx,%%rax"
    : "=a" ( result ) ::  "%rdx" 
  );
  return result;
}
#endif


int main()
{
    uint64_t t = cpucycles();
    sleep(1);
    printf("%f\n", (cpucycles() - t)/1e9 );
    return 0;
}