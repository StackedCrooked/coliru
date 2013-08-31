#include <iostream>
    
template<typename Ret, typename... Args>
Ret foo(Args&&...) {
    std::cout << "not void\n";
    return {};
}

template<typename... Args>
void foo(Args&&...) {
    std::cout << "void\n";
}

int main() {
    foo(3, 'a', 5.4);            //(1): prints "void"
    foo<int, char>(3, 'a', 5.4); //(2): prints "void"
    foo<int>('a', 5.4);          //(3): prints "not void"
    foo<int>(3, 'a', 5.4);       //(4): prints "not void"
}
