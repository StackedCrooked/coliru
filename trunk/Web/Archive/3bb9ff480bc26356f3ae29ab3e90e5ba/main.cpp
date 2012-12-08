#include <fstream>
#include <iostream>

int main()
{
     std::cout << std::boolalpha  << static_cast<bool>(std::ifstream("I_DO_NOT_EXIST")) << std::endl;
}