#include <iostream>
#include <type_traits>

template<typename T>
void foo(T) {
    std::cout << std::is_same<T, char>::value << '\n';
}

int main() {
    foo('a');   
}