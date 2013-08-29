#include <iostream>

int main() {
    auto lambda = [] {
        struct foo {
            void bar() {
                std::cout << "Hello, world!\n";
            }
        };
        
        return foo();
    };
    
    decltype(lambda())().bar();
    
    return 0;
}