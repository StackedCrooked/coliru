#include <stdio.h>

int main()
{
    printf("%*.*f\n", 20, 2, 10.005);   // field width 20, precision 2
    printf("%*.*f\n", -20, -2, 10.005); // -20 results in left aligned output, negative precision (-2) is ignored
}
