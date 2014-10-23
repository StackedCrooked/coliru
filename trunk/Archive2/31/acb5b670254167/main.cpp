#include <stdio.h>

int main() {
    char *c, k = '$';
    int *j;
    
    j = &k;
    printf("%c\n%p\n%c\n", k, j, *j);
    
    c = &k;
    printf("%c\n%p\n%c", k, c, *c);
    
    return 0;
}
