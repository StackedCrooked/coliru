#include <iostream>
#include <exception>

struct MyException : std::exception {
    const char *what() const noexcept override {
        return "My awesome message";   
    }
};

int main() {
    try {
        throw MyException();
    } catch (std::exception ex) {
        std::cout << ex.what();   
    }
}