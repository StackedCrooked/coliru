#include <type_traits>
#include <iostream>

template<typename T>
constexpr T min(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr auto min(T&& t, U&& u) -> decltype(u < t ? std::forward<U>(u) : std::forward<T>(t)) {
    return u < t ? std::forward<U>(u) : std::forward<T>(t);
}

template<typename T, typename U, typename... Args>
constexpr auto min(T&& t, U&& u, Args&&... args) -> decltype(min(min(std::forward<T>(t), std::forward<U>(u)), std::forward<Args>(args)...)) {
    return min(min(std::forward<T>(t), std::forward<U>(u)), std::forward<Args>(args)...);
}

int main() {
    std::cout << min(10, 11, 9, 10, 16, 19, 8);
}