#include <iostream>
#include <sstream>

int main()
{
    std::istringstream stream("a");
    char ch;
    if (stream >> ch) {
       std::cout << "At eof? " << std::boolalpha << stream.eof() << "\n";
       std::cout << "good? " << std::boolalpha << stream.good() << "\n";
    }
}
