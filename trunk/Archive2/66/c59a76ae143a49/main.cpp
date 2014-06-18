#include <iostream>
#include <utility>
#include <list>

template <typename... Args>
struct prank
        : std::integral_constant<std::size_t, 9> 
{
    static_assert(sizeof...(Args) == 999999, "OH NO!");
};

template <template <typename...> class C,typename T, typename ...Args>
struct prank<C<T,Args...>>
        : std::integral_constant<
        std::size_t,
        1+ prank<Args...>::value> {};

int main()
{
    using T = std::list<int>;
    std::cout << prank<T>::value << "\n";
}