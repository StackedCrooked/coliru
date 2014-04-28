#include <string>
#include <iostream>

int main() {
    std::string x(std::move(x));
    std::cout << '"' << x << '"' << std::endl;
}