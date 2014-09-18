#include <iostream>

struct a { int a; };
struct b : a {};

struct c { char a; };
struct d : c {};

int main() {
    std::cout << sizeof(a) << '\n';
    std::cout << sizeof(b) << '\n';
    
    std::cout << sizeof(c) << '\n';
    std::cout << sizeof(d);
}