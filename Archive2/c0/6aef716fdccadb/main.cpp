#include <tuple>
#include <type_traits>

template <typename T, typename Tuple>
struct has_type;

template <typename T>
struct has_type<T, std::tuple<>> : std::false_type {};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};

template <typename T, typename Tuple>
using tuple_contains_type = typename has_type<T, Tuple>::type;

#include <iostream>

int main()
{
    using T = std::tuple<int, double, char>;
    
    std::cout << std::boolalpha;
    
    std::cout << tuple_contains_type<int, T>::value << std::endl;
    std::cout << tuple_contains_type<double, T>::value << std::endl;
    std::cout << tuple_contains_type<char, T>::value << std::endl;
    
    std::cout << tuple_contains_type<float, T>::value << std::endl;
    std::cout << tuple_contains_type<short, T>::value << std::endl;
    std::cout << tuple_contains_type<long, T>::value << std::endl;
    
    std::cout << std::is_same<tuple_contains_type<int, T>, std::true_type>::value << std::endl;
}
