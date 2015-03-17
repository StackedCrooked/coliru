#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int array[] = { 1, 2, 3, 4, 5, -1, -2, -3, -4, -5, 7, 7, 7, 9, 10, -6, -7, -8, -9, -10 };
    int repetitions = 0;

    int compare(const void* pa, const void* pb)
    {
        int a = *(int*)pa;
        int b = *(int*)pb;
        if (a == b)
        {
            repetitions = 1;
            return 0;
        }
        return a < b ? -1 : 1;
    }

    qsort(array, sizeof(array) / sizeof(int), sizeof(int), compare);
    puts(repetitions ? "Yes!" : "No.");
    return 0;
}