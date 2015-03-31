#include <fstream>
#include <iostream>

void f(std::istream&&);

int main()
{
    f(
        false
        ? (std::istream&&) std::ifstream("/tmp")
        : (std::istream&&) std::cin
    );
}