#include <type_traits>

template<typename... Ts>
struct all_of;

template<typename T>
struct all_of<T> : std::integral_constant<bool, T::value> { };

template<typename T, typename... Ts>
struct all_of<T, Ts...> : std::integral_constant<
    bool, T::value && all_of<Ts...>::value> { };

template<typename A, typename... Deriveds>
constexpr bool commonBaseClass()
{
    return all_of<std::is_base_of<A, Deriveds>...>();
}

struct X { };
struct Y : X { };
struct Z : X { };
struct W { };

int main()
{
    // Does not fire
    static_assert(commonBaseClass<X, Y, Z>(), "!");

    // Fires
    static_assert(commonBaseClass<X, Y, Z, W>(), "!");
}
