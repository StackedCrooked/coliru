#include <string>
#include <fstream>
#include <iostream>
 
int main()
{
    std::string filename = "example.123";
 
    std::fstream fs;
 
    fs.open(filename);
 
    if(!fs.is_open())
    {
       fs.clear();
       fs.open(filename, std::ios::out); //Create file.
       fs.close();
       fs.open(filename);
    }
 
    std::cout << std::boolalpha;
    std::cout << "fs.is_open() = " << fs.is_open() << '\n';
    std::cout << "fs.good() = " << fs.good() << '\n';
}