#include <iostream>


int main()
{
    int b = 1;
    const int c = 2;
    int *a = &b;
    a = &c;
    (*a)++;
    printf("a:  %p\n&b: %p\n&c: %p\n", a, &b, &c);
    printf("*a: %d\nb:  %d\nc:  %d\n", *a, b, c);
}
