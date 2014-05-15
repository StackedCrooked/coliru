#include <stdio.h>

int main(void) {
    int blah = 5;
    blah > 12 ? blah < 10
                 ? blah == 5
                     ? printf("win")
                     : printf("3")
                 : printf("2")
             : blah > 2 ? blah == 6 ? printf("nope\n")
                                    : printf("winner!\n")
                        : printf("what?\n");
    return 0;
}