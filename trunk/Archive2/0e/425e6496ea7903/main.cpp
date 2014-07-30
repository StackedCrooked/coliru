#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("%d\n", rand());
    
    srand(1);
    printf("%d\n", rand());
    
    srand(33);
    printf("%d\n", rand());
}
