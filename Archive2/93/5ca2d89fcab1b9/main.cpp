#include <stdio.h>

int main(void) {
    printf("sizeof(char)  = %lu bits\n", sizeof(char) * 8);
    printf("sizeof(short) = %lu bits\n", sizeof(short) * 8);
    printf("sizeof(int)   = %lu bits\n", sizeof(int) * 8);
    printf("sizeof(long)  = %lu bits\n", sizeof(long) * 8);
    printf("sizeof(float) = %lu bits\n", sizeof(float) * 8);
    return 0;
}