#include <iostream>
#include <string>
#include <cstddef>

void print(bool x) {
    std::cout << "bool: " << x << std::endl;
}

void print(std::string const& x) {
    std::cout << "string: " << x << std::endl;
}

template <std::size_t N>
void print(char(&x)[N]) {
    std::cout << "string: " << x << std::endl;
}

int main()
{
    print("hello");
}
