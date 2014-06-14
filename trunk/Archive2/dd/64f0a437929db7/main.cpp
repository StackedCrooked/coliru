#include <iostream>

struct S {
    int foo;  
};

int main() {
    S s{};
    [foo=s.foo]() {
        std::cout << foo;   
    }();
}