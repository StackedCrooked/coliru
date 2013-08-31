#include <stdio.h>

main()
{
    int num, num1;

    num = sizeof(int);
    num1 = sizeof(char);
    printf("Bytes required for int:  %d   Bytes required for char: %d\n", num, num1);
    getchar();
}