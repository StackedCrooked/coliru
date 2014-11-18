#include <type_traits>
#include <utility>
#include <iostream>

template<typename T>
T adder(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename... Args>
typename std::common_type<T, Args...>::type adder(T&& t, Args&&... args) {
    return std::forward<T>(t) + adder(std::forward<Args>(args)...);
}

int main() {
    std::cout << adder(10, 11, 12, 13);
}