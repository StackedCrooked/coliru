#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int *p = new int[1000];

    p[999] = 5;

    printf("P: %d\n", p[999]);

    delete [] p;

    printf("P: %d\n", p[999]);
}