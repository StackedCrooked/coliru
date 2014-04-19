#include <functional>
#include <iostream>

void f(bool _switch) {
    std::cout << "Nothing really" << std::endl;
}

void f(std::function<double (int)> _f) {
    std::cout << "Nothing really, too" << std::endl;
}

int main ( int argc, char* argv[] ) {
    f([&](int _idx){ return 7.9;});
    return 0;
}