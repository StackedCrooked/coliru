#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string words = "Hello from GCC "  __VERSION__ "!";
    std::cout << words << std::endl;
}
