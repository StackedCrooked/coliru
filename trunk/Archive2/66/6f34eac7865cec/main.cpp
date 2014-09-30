#include <iostream>

#if !defined(PORT)
#  define PORT 1234
#endif

int main(void)
{
    printf("%d\n", PORT);

    return 0;
}