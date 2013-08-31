#include <iostream>
#include <string>

void print(bool x) {
    std::cout << "bool: " << x << std::endl;
}

void print(std::string x) {
    std::cout << "string: " << x << std::endl;
}

int main()
{
    print("hello");
}
