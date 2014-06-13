#include <iostream>
#include <type_traits>

int main()
{
    auto l1 = []{};
    auto l2 = []{};
    std::cout << std::is_same<decltype(l1), decltype(l2)>::value << std::endl;
}
