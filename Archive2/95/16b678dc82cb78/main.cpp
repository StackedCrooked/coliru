#include <stdio.h>
#include <time.h>

typedef struct bit {
    int x : 5;
} Bit;
 
int main()
{
    printf("%d, %d", (int) sizeof(Bit), (int) sizeof(int));
}