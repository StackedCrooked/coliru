#include <iostream>
#include <stdexcept>

class foo {
public:
    foo() {
        std::cout << "constructor!\n";
    }
    
    ~foo() {
        std::cout << "destructor!\n";
    }
};

void meh() {
    std::cout << "throwing exception!\n";
    throw std::exception();
}

void bar() {
    foo x;
    meh();
}

int main() {
    try {
        bar();
    } catch (std::exception const&) {
        std::cout << "caught exception!\n";
    }
}
