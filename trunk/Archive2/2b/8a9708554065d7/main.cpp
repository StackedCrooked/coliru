#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

int main()
{
    std::streambuf * b = nullptr;
    
    {
        std::fstream f{ "main.cpp", std::ios::in | std::ios::binary };
        
        if (!f) throw "up";
        
        b = f.basic_ios::rdbuf(nullptr);
    }
    
    assert(((std::filebuf *)b)->is_open());
    
    std::string foo;
    std::istream i{ b };
    
    std::getline(i, foo);
    std::cout << foo;
}
