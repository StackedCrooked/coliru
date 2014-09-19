#include <stdio.h>

void prt_ldbl(long double decker) {
    unsigned char * desmond = (unsigned char *) & decker;
    int i;

    for (i = 0; i < sizeof (decker); i++) {
         printf ("%02X ", desmond[i]);
    }
    printf ("\n");
}

int main()
{
    long double x = 1e-4955L;
    prt_ldbl(x);
}