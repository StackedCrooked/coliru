#include <iostream>
#include <functional>

template<typename T>
void Func(T t, int a) {
    std::cout << "Func " << a << std::endl;
}
template<typename T>
void Func(T t, int a, char ch) {
    std::cout << "Func " << ch << std::endl;
}

int main() {
    auto Fn = [](auto x, auto y) { Func(x, y); };
    Fn(1, 8);
    return 0;
}
