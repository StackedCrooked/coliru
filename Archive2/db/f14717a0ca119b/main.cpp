#include <string>
#include <iostream>

template<class Type>
class X {
public:
    X() { std::cout << "X::X\n"; }
    void a() { std::cout << "X::a\n"; }
    void b() { std::cout << "X::b\n"; }
};

template<>
X<std::string>::X() {
    std::cout << "Specialized\n";
}

int main() {
    X<int>();
    X<std::string>();
}