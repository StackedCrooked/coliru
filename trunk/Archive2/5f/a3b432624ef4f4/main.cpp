#include <iostream>

struct S {
    S() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    S(const S&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    S(S&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    ~S() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

S make_S() {
    S tmp;
    return tmp;
}

int main() {
    S obj = make_S();
}