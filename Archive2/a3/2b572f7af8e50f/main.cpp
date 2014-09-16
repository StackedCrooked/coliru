#include <iostream>
#include <type_traits>
#include <utility>

template <typename... Ts>
struct B {};

template <typename... Ts>
struct D : B<Ts...> {};

template <typename... Ts>
struct Other {};

namespace detail
{
    template <template <typename...> class Base, typename Derived>
    struct is_derived_from_template
    {
        using U = typename std::remove_cv<Derived>::type;
        
        template <typename... Args>
        static auto test(Base<Args...>*)
            -> typename std::integral_constant<bool, !std::is_same<U, Base<Args...>>::value>;
        
        static std::false_type test(void*);
        
        using type = decltype(test(std::declval<U*>()));
    };
}

template <template <typename...> class Base, typename Derived>
using is_derived_from_template = typename detail::is_derived_from_template<Base, Derived>::type;

int main()
{
    std::cout << is_derived_from_template<B, D<int, int>>::value << std::endl;
    std::cout << is_derived_from_template<B, D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_template<B, const D<int, char, float>>::value << std::endl;
    
    std::cout << is_derived_from_template<B, Other<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_template<B, int>::value << std::endl;
    std::cout << is_derived_from_template<B, B<int,int>>::value << std::endl;
}
