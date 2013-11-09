#include <setjmp.h>
int main()
{    
    int printf(const char *, ... );
    int scanf(const char *, ... );
    char m[sizeof(jmp_buf)+sizeof(int)*3] = {0};
    printf("Enter two numbers:\n") && scanf("%d %d",(int*)(m+sizeof(jmp_buf)*3),(int*)(m+sizeof(jmp_buf)*2)) && ( ( *(int*)(m+sizeof(jmp_buf)*3) < *(int*)(m+sizeof(jmp_buf)*2) && ( *(int*)(m+sizeof(jmp_buf)) = *(int*)(m+sizeof(jmp_buf)*3), 1)  ) ||  ( *(int*)(m+sizeof(jmp_buf)) = *(int*)(m+sizeof(jmp_buf)*2), *(int*)(m+sizeof(jmp_buf)*2) = *(int*)(m+sizeof(jmp_buf)*3), 1 ) ) && setjmp((void*)m) <= *(int*)(m+sizeof(jmp_buf)*2) && printf("%d\n",*(int*)(m+sizeof(jmp_buf))) && (longjmp((void*)m,++*(int*)(m+sizeof(jmp_buf))),1);
}