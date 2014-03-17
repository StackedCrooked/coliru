#include <stdio.h>
#include <stdlib.h>

#define maxint(a,b) ({int _a = (a), _b = (b); _a > _b ? _a : _b; })

int main() {
    printf("%d", maxint(-100,100));
    
    return 0;
}
