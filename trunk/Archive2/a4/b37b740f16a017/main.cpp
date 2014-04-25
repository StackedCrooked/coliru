#include <iostream>
#include <string>
#include <type_traits>

// what if I only wanted ints?

//template<typename T>
//T add(T x, T y) {
//    return x + y;
//}

// current way of doing it now
template<typename T, typename U = typename std::enable_if<std::is_arithmetic<T>::value>::type>
T add(T x, T y) {
    return x + y;
}

// how concepts would do it:
//Arithmetic add(Arithmetic x, Arithmetic y) {
//    return x + y;
//}

int main() {
    std::cout << add(10, 11) << '\n'
              << add(10.f, 12.f) << '\n'
              << add(std::string("Hello"), std::string(" World")) << '\n'; // fancy error
}