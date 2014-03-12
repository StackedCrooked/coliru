#include <iostream>
#include <string>

int main()
{
    std::cout << "hello " + std::string("world\n");
    std::cout << std::string("hello ") + "world\n";
}