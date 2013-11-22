#include <type_traits>

template<class T, class = void>
struct is_stateless : std::false_type{};

template<class T>
struct is_stateless<T, decltype(+std::declval<T&>(), void())> : std::true_type{};

#include <iostream>

int main()
{
    int a = 0;
    auto l1 = [a](){ return 1; };
    auto l2 = [](){ return 2; };
    auto l3 = [&a](){ return 2; };
     
    std::cout << std::boolalpha << is_stateless<decltype(l1)>::value << "\n";
    std::cout << std::boolalpha << is_stateless<decltype(l2)>::value << "\n";
    std::cout << std::boolalpha << is_stateless<decltype(l3)>::value << "\n";
}