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
    template <typename... Args>
    std::true_type test(B<Args...>*);
    std::false_type test(void*);
}

template <typename T>
struct is_derived_from_B : decltype(detail::test(std::declval<typename std::remove_cv<T>::type*>()))
{
};

int main()
{
    std::cout << is_derived_from_B<D<int, int>>::value << std::endl;
    std::cout << is_derived_from_B<D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<const D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<Other<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<int>::value << std::endl;
}
