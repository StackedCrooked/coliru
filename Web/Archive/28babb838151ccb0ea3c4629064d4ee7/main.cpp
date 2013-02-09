#include <iostream>
#include <type_traits>

template<int I, int... Args>
struct Sum : std::integral_constant<int, I + Sum<Args...>::value>{};

template<int I>
struct Sum<I> : std::integral_constant<int, I> {};

int main() {
    std::cout << Sum<0,1,2,3,4,5,6,7,8>::value;
}