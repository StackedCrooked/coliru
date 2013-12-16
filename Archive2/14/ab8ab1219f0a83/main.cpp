#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

int main()
{
    std::stringstream ss("hi there\r\n");
    std::string line;
    getline(ss, line);
    std::cout << '[' << line << "]\n";
    assert(line.length() == 8);
}
