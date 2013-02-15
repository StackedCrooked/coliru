#include <fstream>
#include <iostream>

int main()
{
     std::cout << static_cast<bool>(std::ifstream("I_DO_NOT_EXIST")) << std::endl;
}dddssss