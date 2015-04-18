#include <iostream>
#include <type_traits>

struct E { virtual void foo() = 0; };

template<typename T>
struct is_abstract_test
{
    static constexpr bool external = std::is_abstract<E>::value;

    struct I { virtual void foo() = 0; };
    static constexpr bool internal = std::is_abstract<I>::value;
};

int main()
{   
    std::cout << is_abstract_test<int>::external << std::endl;
    std::cout << is_abstract_test<int>::internal << std::endl;
}
