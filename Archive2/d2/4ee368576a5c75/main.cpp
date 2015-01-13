#include <fstream>
#include <iostream>
 
int main()
{
    std::ifstream fs("test.txt");
    std::filebuf fb;
    fb.open("test.txt", std::ios_base::in);
    std::cout << std::boolalpha
              << "direct call: " << fb.is_open() << '\n'
              << "through streambuf: " << fs.rdbuf()->is_open() << '\n'
              << "through fstream: " << fs.is_open() << '\n';
}