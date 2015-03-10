#include <stdio.h>
#include <stdlib.h>
 
int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}
 
int main(void)
{
    int i;
    int ints[] = { -2, 99, 0, -743, 2, 3, 4 };
    int size = sizeof ints / sizeof *ints;
 
    qsort(ints, size, sizeof(int), compare_ints);
 
    for (i = 0; i < size; i++) {
        printf("%d ", ints[i]);
    }
 
    printf("\n");
 
    return EXIT_SUCCESS;
}