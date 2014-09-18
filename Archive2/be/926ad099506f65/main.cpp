#include <stdio.h>

int calc5xplusy(int x, int y, int* res) {
    *res = 5*x + y;
    return 0; // wrong
}

    typedef struct Test {
        int x;
        int y;
        int overflow;
    } Test;

int main(void)
{
    int numTests;
    int i;
    printf("an unsigned int is %lu bits!\n", 8 * sizeof (unsigned int));

    Test tests[] = {
        {1, 2, 0},
        {1000000000, 1000000000, 1},
    };
    
    numTests = sizeof(tests)/sizeof(tests[0]);
    for (i = 0; i < numTests; ++i) {
        int res, overflow;
        overflow = calc5xplusy(tests[i].x, tests[i].y, &res);
        if (overflow != tests[i].overflow)
            printf("Test #%d failed\n", i);
    }
    return 0;    
}