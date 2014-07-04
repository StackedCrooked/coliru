#include <iostream>
#include <type_traits>
#include <utility>

template<class T, int N, T const (&)[N]>
struct foo {};

template<class T, int N>
constexpr auto unpack(T const (&a)[N])
{
    return foo<T, N, a>{};
}

constexpr int arr[] = { 1, 2 };

int main()
{
    using pack = decltype(unpack(arr));
}
