#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    
    char* s = malloc(32);
    sprintf(s,"oula %d\n",10);
 
    printf("%s",s);
    
}