#include <iostream>
#include <string>

struct A {
    int a;
    std::string s;
};

struct B {
    int a;
    std::string s;
    B(double) { };
};

int main () {
    std::cout << std::boolalpha;
    std::cout << std::is_constructible<A, int, std::string>::value << '\n';
    std::cout << std::is_constructible<B, int, std::string>::value << '\n';
    A a{1, ""};//but this works
    //B b{1, ""};//aggregate init unavailable
    std::cout << std::is_constructible<A, double>::value << '\n';
    std::cout << std::is_constructible<B, double>::value << '\n';
    //A a2(0.5);//no A(double) present
    B b2(0.5);
}