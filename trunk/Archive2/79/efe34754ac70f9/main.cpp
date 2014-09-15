#include <iostream>
#include <utility>
#include <type_traits>

template <typename... Ts>
struct B {};

template <typename... Ts>
struct D : B<Ts...> {};

template <typename... Ts>
struct Other {};

namespace detail
{
    template <template <typename...> class T>
    struct is_derived_from_variadic
    {
        template <typename... Args>
        static std::true_type test(T<Args...>*);
        
        static std::false_type test(void*);
    };
}

template <template <typename...> class Base, typename Derived>
using is_derived_from_variadic = decltype(detail::is_derived_from_variadic<Base>::test(std::declval<typename std::remove_cv<Derived>::type*>()));

int main()
{
    std::cout << is_derived_from_variadic<B, D<int, int>>::value << std::endl;
    std::cout << is_derived_from_variadic<B, D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_variadic<B, const D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_variadic<B, Other<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_variadic<B, int>::value << std::endl;
}
