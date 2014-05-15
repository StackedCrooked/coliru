#include <stdio.h>

int main(void) {
    int blah = 5;
    blah > 2 ? blah < 10 ? blah == 5 ? printf("win") : printf("3") : printf("2") : printf("1");
    return 0;
}