#include <type_traits>
#include <iostream>

template <template <typename> class P, typename T> 
using foo = P<T>; 

template <template <typename...> class P, typename T> 
struct partial {
    template <typename... Ts> 
    using type = P<T, Ts...>;
};

template <typename T> 
using is_int = partial<std::is_same, int>::type<T>; 

int main() { 
    std::cout << is_int<int>::value << ' ' << is_int<double>::value << '\n';
}
