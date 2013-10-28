#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(0));    
    int x = rand();
    
#ifdef AND
    printf("%d", x & 1);
#endif
    
#ifdef MOD
    printf("%d", x % 2);
#endif
}