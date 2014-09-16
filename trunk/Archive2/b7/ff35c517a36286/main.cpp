#include <iostream>

int main() {
    int foo = 0;
    int bar = 0;
    for(unsigned i = 0; i < 4; ++i) {
        ++foo;
    }
    
    for(unsigned i = 0; i < 3; ++i) {
        ++bar;
    }
    
    foo = bar;
    
    int a = 4;
    a -= 1;
    std::cout << a << '\n' << foo << '\n';
}