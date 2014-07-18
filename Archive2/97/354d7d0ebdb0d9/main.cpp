#include<stdio.h>

int fromFloat(int a);

int main()
{

    printf("%d\n", fromFloat(1.5));
    return 0;
}

int fromFloat(int a) {
    return a;
}