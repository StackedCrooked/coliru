#include <iostream>
#include <fstream>

int main()
{
    std::ifstream f("main.cpp", std::ios::in);
    std::string input;
    std::getline(f, input, 'i');
    std::cout << input;
}
