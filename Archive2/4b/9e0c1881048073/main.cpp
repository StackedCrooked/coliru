#include <stdio.h>


void func(int *tab)
{
    return;
}

int main()
{
    int maxsize = 999*999;
    int tabs[maxsize][6] ;
    
    tabs[0][0] = 0 ;
    
    printf( "%d\n", tabs[0][0] ) ;

    return 0;
}