#include <stdio.h>

int main() {
    int x[] = {1, 2, 3, 4};
    for (int i : x)
        printf("%d", i);
    return 0; 
}