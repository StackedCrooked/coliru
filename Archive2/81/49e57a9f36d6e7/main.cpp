#include <iostream>

const char *foo() {std::cout << "foo "; return "";}
const char *bar() {std::cout << "bar "; return "";}

int main() {
    std::cout << foo() << bar();
}