#include <iostream>


auto foo();


int main() {
    std::cout << foo();
}

auto foo() {
    return 1234;
}