#include <type_traits>

template<bool b>
using stdbool_t = std::integral_constant<bool, b>;

template<class T, class U = std::true_type>
struct trait
    : std::false_type
{};

struct foo {};
struct bar : foo {};

template<class T>
struct trait<T, stdbool_t<std::is_base_of<foo, T>{}>>
    : std::true_type
{};


#include <iostream>

int main()
{
    std::cout << std::boolalpha << trait<int>::value << "\n";
    std::cout << std::boolalpha << trait<foo>::value << "\n";
    std::cout << std::boolalpha << trait<bar>::value << "\n";
}