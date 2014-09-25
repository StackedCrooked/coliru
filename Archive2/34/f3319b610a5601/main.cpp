#include <iostream>
#include <functional>

void foo(std::function<int(int, int)> func) {
    std::cout << func(3, 4);
}

template<typename F>
void bar(F func) {
    std::cout << func(3, 4);
}

int main() {
    auto lambda = [] (auto a, auto b) {return a + b;};
    foo(lambda);
    std::cout << std::endl;
    bar(lambda);
}
