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
    struct is_derived_from_template
    {
        template <typename... Args>
        static std::true_type test(T<Args...>*);
        
        static std::false_type test(void*);
    };
}

template <template <typename...> class Base, typename Derived>
using is_derived_from_template = decltype(detail::is_derived_from_template<Base>::test(std::declval<typename std::remove_cv<Derived>::type*>()));

int main()
{
    std::cout << is_derived_from_template<B, D<int, int>>::value << std::endl;
    std::cout << is_derived_from_template<B, D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_template<B, const D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_template<B, Other<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_template<B, int>::value << std::endl;
}
