#include <iostream>
#include <tuple>
#include <type_traits>

template <typename T, typename U>
struct has_type;

template <typename T>
struct has_type<T, std::tuple<>> : std::false_type {};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};

int main()
{
    using T = std::tuple<int, double, char>;
    
    std::cout << has_type<int, T>::value << std::endl;
    std::cout << has_type<double, T>::value << std::endl;
    std::cout << has_type<char, T>::value << std::endl;
    
    std::cout << has_type<float, T>::value << std::endl;
    std::cout << has_type<short, T>::value << std::endl;
    std::cout << has_type<long, T>::value << std::endl;
}
