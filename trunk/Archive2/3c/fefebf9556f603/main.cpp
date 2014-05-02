#include <iostream>
#include <cstdlib>

template <typename... Ts>
struct Set {};

template <typename T, typename TS>
struct MemberOf;

template <typename T, typename... Ts>
struct MemberOf<T, Set<T, Ts...>> {
    static constexpr bool value = true;
};

template <typename T>
struct MemberOf<T, Set<>> {
    static constexpr bool value = false;
};

template <typename T, typename U, typename... Ts>
struct MemberOf<T, Set<U, Ts...>> {
    static constexpr bool value = MemberOf<T, Set<Ts...>>::value;
};

int main()
{
    Set<int, double, char, short> s1;
    std::cout << std::boolalpha << MemberOf<float, decltype(s1)>::value << '\n';
    std::cout << std::boolalpha << MemberOf<short, decltype(s1)>::value << '\n';
    std::cout << std::boolalpha << MemberOf<double, decltype(s1)>::value << '\n';
    std::cout << std::boolalpha << MemberOf<long, decltype(s1)>::value << '\n';
    return EXIT_SUCCESS;
}