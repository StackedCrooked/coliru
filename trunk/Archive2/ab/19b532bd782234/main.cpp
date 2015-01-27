#include <stdio.h>

int main(void) {
    for (int i = 0; i < 10; i++) {
        if (i == 3) {
            break;
        }
        printf("%d \n", i);
    }
    
    printf("\n");
    
    for (int i = 0; i < 10; i++) {
        if (i == 3) {
            continue;
        }
        printf("%d \n", i);
    }
}