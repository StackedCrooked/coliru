// Stupid
// Just stupid.

#include <type_traits>
#include <iostream>
#include <string>

template<typename T>
using EnableIf = typename std::enable_if<T::value>::type;

template<typename T, EnableIf<std::is_arithmetic<T>>...>
auto operator+(const std::string& str, const T& t) -> decltype(str + std::to_string(t)) {
    return str + std::to_string(t);
}

int main() {
    std::string hello = "Hello ";
    std::cout << (hello + 100) << '\n';
}