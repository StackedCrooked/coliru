#include <stdio.h>
#include <stdlib.h>
 
int compare_ints(const void* a, const void* b)
{
    const int *arg1 = a;
    const int *arg2 = b;
 
    return *arg2 - *arg1;
}
 
int main(void)
{
    int i;
    int ints[] = { -2, 99, 0, -743, 2, 3, 4 };
    int size = sizeof(ints) / sizeof(int);
 
    qsort(ints, size, sizeof(int), compare_ints);
 
    for (i = 0; i < size; i++) {
        printf("%d ", ints[i]);
    }
 
    printf("\n");
 
    return EXIT_SUCCESS;
}