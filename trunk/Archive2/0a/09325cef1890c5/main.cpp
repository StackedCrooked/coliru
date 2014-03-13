#include <stdio.h>
#include <stdlib.h>

int main  ()
{
    int i ;
    
    for(i=32; i<256 ;i++)
    {
        if(i%16 == 0)
        printf("\n") ;
        
            printf("%3d  %c",  i , i);
        
        
        
    }
    
}

