#include <iostream>
#include <type_traits>

template<class T, T& t>
struct foo {};

template<class T, int N>
auto unpack(T (&a)[N])
{
    return foo<T, a>{};
}

int arr[10];

int main()
{
    auto x = unpack(arr);
}