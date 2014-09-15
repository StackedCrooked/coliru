#include <iostream>
#include <type_traits>
#include <utility>

template <typename... Ts>
struct B
{
    using Types = std::tuple<Ts...>;
};

template <typename... Ts>
struct D : B<Ts...>
{
};

namespace detail
{
    template <typename T>
    struct is_derived_from_B
    {
        using yes = char;
        using no = long;
                
        template <typename... Args>
        static yes test(B<Args...>*);
        
        static no test(...);
        
        static constexpr bool value = sizeof(test(std::declval<T*>())) == sizeof(yes);
    };
}

template <typename T>
struct is_derived_from_B : std::conditional<detail::is_derived_from_B<T>::value, std::true_type, std::false_type>::type {};

int main()
{
    std::cout << is_derived_from_B<D<int, int>>::value << std::endl;
    std::cout << is_derived_from_B<D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<int>::value << std::endl;
}
