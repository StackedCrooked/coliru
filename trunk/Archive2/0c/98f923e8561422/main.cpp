#include <iostream>

struct S {
    S() { std::cout << "S()\n"; }
    S(const S&) { std::cout << "S(const S&)\n"; }
    S(S&&) { std::cout << "S(S&&)\n"; }
    ~S() { std::cout << "~S()\n"; }

    S& operator=(const S&) {
        std::cout << "S& operator=(const S&)\n";
        return *this;
    }

    S& operator=(S&&) {
        std::cout << "S& operator=(S&&)\n";
        return *this;
    }
};

int main() {
    auto x = S{};
}