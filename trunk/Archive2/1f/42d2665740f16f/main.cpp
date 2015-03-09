#include <stdio.h>
#include <stdlib.h>

static int arrays[] = {[0 ... 9] = -1};

int main()
{
    printf("%d\n", arrays[9]);
}

