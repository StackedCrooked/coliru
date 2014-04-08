#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<char> msg = {'1', '2', '3', '\0'};
    std::cout << msg.size() << std::endl;
}
