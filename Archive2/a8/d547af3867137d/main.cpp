#include <type_traits>
#include <iostream>

template<typename T, typename U>
constexpr bool is_same = std::is_same<T, U>();

int main()
{
    std::cout << is_same<int, int>;
}