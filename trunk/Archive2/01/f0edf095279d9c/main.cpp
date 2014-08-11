#include <iostream>
#include <type_traits>

template<typename T, 
         typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
void foo(const T& t) {
    std::cout << "integer\n";
}

template<typename T, 
         typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
void foo(const T& t) {
    std::cout << "float\n";
}

template<typename T, 
         typename std::enable_if<!std::is_integral<T>::value && 
                                 !std::is_floating_point<T>::value, int>::type = 0>
void foo(const T& t) {
    std::cout << "other\n";
}

int main() {
    foo(1);
    foo(1.4);
    foo("hello");
}