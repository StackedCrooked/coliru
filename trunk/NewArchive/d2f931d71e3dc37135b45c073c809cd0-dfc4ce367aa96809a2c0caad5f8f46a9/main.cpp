long long int fact(int n)
{
    static long long int result = 1;

    if(n <= 1) {
        long long int temp = result;
        result = 1;
        return temp;
    } else {
        result *= n;
        return fact(n - 1);
    }
}

#include <stdio.h>

void display(int n) {
    printf("fact(%d) = %lld\n", n, fact(n));
}

int main(void) {
    display(3);
    display(5);
    display(6);
    display(13);
    return 0;
}