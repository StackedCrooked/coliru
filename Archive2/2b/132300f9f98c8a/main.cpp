#include <stdio.h>

int set_bit(int a, int bitmask) {
    return a | bitmask;
}

int clear_bit(int b, int bitmask) {
    return b & ~bitmask;
}

int toggle_bit(int d, int bitmask) {
    return d ^ bitmask;
}

int get_bit(int c, int bitmask) {
    return ((c & bitmask) != 0) ? 1 : 0;
}

int bin(int a, int b, int c, int d) {
    return (a << 3) | (b << 2) | (c << 1) | d;
}

int main(void) {
    int ten = bin(1,0,1,0);
    printf("%d\n", set_bit(ten, bin(0,0,0,0))); // 1010
    printf("%d\n", set_bit(ten, bin(1,0,1,0))); // 1010
    printf("%d\n", set_bit(ten, bin(0,1,0,0))); // 1110
    printf("%d\n", set_bit(ten, bin(0,0,0,1))); // 1011
    printf("%d\n", set_bit(ten, bin(0,1,0,1))); // 1111

    return 0;
}