#include <stdio.h>

void lenprinter(int v[5])
{
    printf("%lu\n", sizeof v);
}

int main(void)
{
    int v[5];
    
    printf("%lu\n", sizeof v);
    
    lenprinter(v);
    
    return 0;
}
