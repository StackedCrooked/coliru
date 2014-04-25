#include <fstream>
#include <iostream>

int main()
{
    std::streambuf * b = nullptr;
    
    {
        std::fstream f{ "main.cpp", std::ios::in | std::ios::binary };
        //b = ((std::ios &)f).rdbuf(nullptr);
        b = f.basic_ios::rdbuf(nullptr);
    }
    
    std::istream i{ b };
}
