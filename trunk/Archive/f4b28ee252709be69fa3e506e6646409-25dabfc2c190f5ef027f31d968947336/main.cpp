#include <iostream>

struct X {
    X(std::initializer_list<int> list) { std::cout << "list" << std::endl; }
    X(float f) { std::cout << "float" << std::endl; }
};

int main() {
    int x { 1.0f };
    X a(1);     // float (implicit conversion)
    X b{1};     // list
    X c(1.0f);  // float
    X d{1.0f};  // list (narrowing conversion) ARG!!!

    // warning: narrowing conversion of '1.0e+0f' from 'float' to 'int'
    // inside { } [-Wnarrowing]
}