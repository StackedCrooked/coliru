#include <iostream>
#include <type_traits>

template<typename T>
void f(T x) {
    std::cout << std::is_const<T>() << '\n';
    std::cout << std::is_const<T const>() << '\n';
}

int main() {
    int x = 1;
    f<int&>(x);
    return 0;
}
