#include <stdio.h>

int main()
{
    int num, num1;

    num = sizeof(int);
    num1 = sizeof(char);
    printf("Bytes required for int:  %d   Bytes required for char: %d\n", num, num1);
    return 0;
}