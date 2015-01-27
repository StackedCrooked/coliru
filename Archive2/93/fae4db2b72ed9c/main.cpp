#include <stdio.h>

typedef enum {false, true} bool;

int main(void) {
    bool b = true;
    if (b) {
        printf("%d\n", b);
    }
    return 0;
}