#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(void)
{
    srand(time(0)); //use current time as seed for random generator
    for ( int i =0 ; i < 10 ; i++ )
    {
        int random_variable = rand()%10000 + 0;
        printf("Random value: %d\n", random_variable);
    }
}