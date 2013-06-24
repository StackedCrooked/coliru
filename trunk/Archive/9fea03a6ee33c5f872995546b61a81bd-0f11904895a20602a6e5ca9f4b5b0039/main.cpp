#include <iostream>


auto foo() -> decltype(12334) {
    return 1234;
}

int main() {
    std::cout << foo();
}

