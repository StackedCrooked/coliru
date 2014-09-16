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
    template <typename Derived>
    struct is_derived_from_B
    {
        using U = typename std::remove_cv<Derived>::type;
                
        template <typename... Args>
        static auto test(B<Args...>*)
            -> typename std::integral_constant<bool, !std::is_same<U, B<Args...>>::value>;
        
        static std::false_type test(void*);
        
        using type = decltype(test(std::declval<U*>()));
    };
}

template <typename Derived>
using is_derived_from_B = typename detail::is_derived_from_B<Derived>::type;

int main()
{
    std::cout << is_derived_from_B<D<int, int>>::value << std::endl;
    std::cout << is_derived_from_B<D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<const D<int, char, float>>::value << std::endl;
    
    std::cout << is_derived_from_B<Other<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<int>::value << std::endl;
    std::cout << is_derived_from_B<B<int,int>>::value << std::endl;
}
