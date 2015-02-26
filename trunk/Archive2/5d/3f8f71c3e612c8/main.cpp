#include <type_traits>
#include <iostream>

template <typename... T>
struct All : std::true_type {};

template <typename Head, typename... Tail>
struct All<Head, Tail...> : std::conditional<Head::value, All<Tail...>, std::false_type>::type {};

int main() {
    std::cout << All<std::true_type, std::true_type, std::false_type>::value;
    std::cout << All<std::true_type, std::true_type, std::true_type>::value;
}