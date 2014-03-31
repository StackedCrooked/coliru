#include <stdio.h>

int main() {
    int i = 0x7fffffff;
    int ii = 0x0000000f;

    if ((i + 1) < ii)
        printf ("yes1 %#x\n", i + 1);

    if ((i + 1) == ii)
        printf ("yes2 %#x\n", i + 1);

    if ((i + 1) > ii)
        printf ("yes3 %#x\n", i + 1);

    return 0;
}
