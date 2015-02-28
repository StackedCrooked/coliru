#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *i = (int*)malloc(sizeof(int));
    *i = 5;
    int *j = i + 1;
    for (;; ++j)
    {
        *j = 1;
        puts("writing to the either");
    }
    free(i);
}