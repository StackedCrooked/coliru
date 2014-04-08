#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string msg = {'1', '2', '3', '\0'};
    std::cout << msg.size() << std::endl;
    std::string msg2 = msg.c_str();
    std::cout << msg2.size() << std::endl;
}
