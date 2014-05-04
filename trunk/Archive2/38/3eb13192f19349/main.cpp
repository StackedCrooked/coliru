#include <iostream>
#include <stdexcept>

void foo() {
    try {
        throw std::runtime_error("test");
    } catch (std::exception &e) {
        throw;   
    }
}

int main() {
    try {
        foo();
    } catch (std::runtime_error &e) {
        std::cout << e.what();   
    }
}