#include <stdio.h>
 
/* function prototype (not part of a function definition) */
int simple_add (int lho, int rho);
 
int lho=10;  /* no conflict with "lho" in function prototype */
 
int main(void)
{
    printf("lho=%d\n",lho);
    printf("%d\n", simple_add(1,2));
    printf("lho=%d\n",lho);
 
    return 0;
}
 
int simple_add (int lho, int rho)
{
    return (lho+rho);
}