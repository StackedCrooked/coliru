#include <cstdio>

void foo(int* arr) {}

// uncoment the next line and you get a redefinition error
// void foo(int arr[]) {}

void bar(int arr[])
{
    ++arr;
    arr += 1;
    *arr = 42;
}

int main()
{
    int a[] = {1,2,3};
    bar(a);
    printf("%d", a[2]);
}