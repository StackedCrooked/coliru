#include <iostream>
    
template<typename Ret, typename T>
Ret foo(T&&) {
    std::cout << "not void\n";
    return {};
}

template<typename T>
void foo(T&&) {
    std::cout << "void\n";
}

int main() {
    foo<int>(3);
}
