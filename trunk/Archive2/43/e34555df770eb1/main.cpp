#include <memory>
#include <fstream>
#include <string>
#include <iostream>

int main()
{
    std::unique_ptr<std::istream> up(new std::ifstream("main.cpp"));
    std::string line;
    
    while(std::getline(*up, line)) std::cout << line << '\n';
}
