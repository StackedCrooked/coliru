#include <iostream>
#include <cstdlib>
#include <type_traits>

template <typename...>
struct Set {};

template <typename, typename>
struct MemberOf : public std::false_type {};

template <typename T, typename Head, typename... Tail>
struct MemberOf<T, Set<Head, Tail...>> :
  public std::integral_constant<bool,
    std::is_same<T, Head>::value ||
    MemberOf<T, Set<Tail...>>::value> {};

int main()
{
    Set<int, double, char, short> s1;
    std::cout << std::boolalpha << MemberOf<float, decltype(s1)>::value << '\n';
    std::cout << std::boolalpha << MemberOf<short, decltype(s1)>::value << '\n';
    std::cout << std::boolalpha << MemberOf<double, decltype(s1)>::value << '\n';
    std::cout << std::boolalpha << MemberOf<long, decltype(s1)>::value << '\n';
    return EXIT_SUCCESS;
}