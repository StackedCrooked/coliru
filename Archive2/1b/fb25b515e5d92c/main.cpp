#include <iostream>

int main() {
    std::cout << R"(a"b"c")";
    std::cout << '\n';
    std::cout << R"aa(a("b"))aa";
}