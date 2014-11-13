#include <stdio.h>
#include <time.h>
 
int main(void)
{
    int i = 0 , n = 4
    , res = 0;
    for(i = 0 ; i < 24 ; i++){
        if(i%10 == n)res ++;
        if(i/10 == n) res ++;
    }
    
    printf("%d\n", res);
 
    return 0;
}