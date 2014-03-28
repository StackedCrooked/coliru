struct A {
    explicit operator bool() const noexcept {
        return true;
    }
};

#include <iostream>

int main() {
    A a;
    if(a) {
        std::cout << "!";
    }
}