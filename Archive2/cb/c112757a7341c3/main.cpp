#include <stdio.h>
#include <setjmp.h>
int main()
{
    char m[24+sizeof(jmp_buf)] = {0,3,6,7,7,8,1,4,8,9,7,5,2,0,22,23,62,77,90,91,98,101,104};
    setjmp((void*)(m+24)) < 13 && putchar(m[m[m[0]+1]+13]+10) && (longjmp((void*)(m+24),++*m),1);
}

