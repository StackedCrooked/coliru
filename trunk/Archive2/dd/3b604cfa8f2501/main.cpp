#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string msg = {'1', '2', '3', '\0'};
    std::cout << msg.size() << std::endl;
}
