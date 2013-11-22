#include <stdio.h>


void func(int *tab)
{
    return;
}

int main()
{
    int maxsize = 999*999;
    int tabs[maxsize][6];
    
    scanf( "%d", tabs[maxsize-1][0] ) ;
    
    printf( "%d\n", tabs[maxsize-1][0] ) ;

    return 0;
}