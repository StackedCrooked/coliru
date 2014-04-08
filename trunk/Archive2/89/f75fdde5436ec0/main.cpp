#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
struct outer
{
    template <typename U>
    struct inner
    {
        U data{};
    };
};

template <typename T, typename U>
bool operator==(typename outer<T>::template inner<U> const &lhs, typename outer<T>::template inner<U> const &rhs)
{ return lhs.data == rhs.data; }

int main() {
    outer<int>::inner<float> oi1, oi2;
    std::cout << (oi1 == oi2) << std::endl;
}