#include <type_traits>
#include <iostream>

std::integral_constant<bool, true> a;

int main()
{
    auto x = !a;
    std::cout << std::is_same<decltype(x), bool>{};
}
