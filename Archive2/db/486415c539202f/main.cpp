#include <fstream>
#include <iostream>

void f(std::istream&);

int main()
{
    f(
        false
        ? std::ifstream("/tmp")
        : std::cin
    );
}