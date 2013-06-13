#include <type_traits>
#include <iostream>

template<typename... Args>
using CommonType = typename std::common_type<Args...>::type;

template<typename T>
constexpr T min(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr auto min(T&& t, U&& u) -> CommonType<T,U> {
    return t < u ? std::forward<T>(t) : std::forward<U>(u);
}

template<typename T, typename U, typename... Args>
constexpr auto min(T&& t, U&& u, Args&&... args) -> CommonType<T,U,Args...> {
    return min(min(std::forward<T>(t),std::forward<U>(u)), std::forward<Args>(args)...);
}

int main() {
    auto i = min(1,2,3,4,5,-1,11,1291,1299181);
    std::cout << i;
}