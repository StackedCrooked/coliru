#include <iostream>
#include <typeinfo>

int foo() {return 1;}
double foo(int) {return 1;}


int main() {
    std::cout << typeid(decltype(void(foo()))).name() << std::endl;
    std::cout << typeid(decltype(foo())).name() << std::endl;
    std::cout << typeid(void(int)).name() << std::endl;
    std::cout << typeid(void).name() << std::endl;
    
    decltype(1) x = 1;
}