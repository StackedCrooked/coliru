int factorial(int n)
{
    static int m = 1;
    m *= n;
    if (n > 1)
        factorial(n - 1);
    return m;
}

#include <stdio.h>

void display(int n) {
    printf("factorial(%d) = %d\n", n, factorial(n));
}

int main(void) {
    display(3);
    display(5);
    display(6);
    display(1);
    return 0;
}