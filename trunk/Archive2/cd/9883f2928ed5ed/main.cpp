#include <stdio.h>

typedef enum {false, true} bool;

bool is_even(int x) {
    return x % 2 == 0 ? true : false;        
}

int main(void) {
    printf("%d\n", is_even(0));
    printf("%d\n", is_even(3));
    printf("%d\n", is_even(134912372));
    printf("%d\n", is_even(245));
    return 0;
}