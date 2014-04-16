#include <stddef.h>

#define countof(x) (sizeof(x) / sizeof((x)[0]))

constexpr int sum(const int* arr, size_t count)
{
    return (count == 0 ? 0 : arr[0] + sum(arr+1, count-1));
}

void f()
{
    constexpr int arr2[] { 1, 2, 3, 4, 5, 0, 6 };
    constexpr int sumvalue2 = sum(arr2, countof(arr2));
}

int main() {}