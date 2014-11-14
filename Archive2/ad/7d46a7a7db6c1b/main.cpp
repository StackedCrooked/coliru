#include <iostream>

template<typename T>
void println(T&& t) {
    std::cout << std::forward<T>(t) << ": " << __PRETTY_FUNCTION__ << '\n';
}

template<typename T, typename... Args>
void println(T&& t, Args&&... args) {
    std::cout << std::forward<T>(t) << ": " << __PRETTY_FUNCTION__ << '\n';
    println(std::forward<Args>(args)...);
}

int main() {
    println(10, 11, "hello", "world", 'a', 3.14);
}