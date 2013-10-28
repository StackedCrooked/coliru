#include <cstdio>

int main()
{
    int x = 5;
    
#ifdef AND
    printf("%d", x & 1);
#endif
    
#ifdef MOD
    printf("%d", x % 2);
#endif
}