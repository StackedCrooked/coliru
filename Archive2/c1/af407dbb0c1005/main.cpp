#include <iostream>
#include <sstream>
#include <string>
#include <limits>

int main()
{
    unsigned int value = 8;
    std::string negString = "-1";
    std::istringstream negStream(negString);
    negStream >> value;
    std::cout << "Value:  " << value << std::endl;
    return 0;
}
