#include <fstream>
#include <iostream>

int main()
{
    system("touch I_DO_NOT_EXIST");
     std::cout << std::boolalpha << static_cast<bool>(std::ifstream("I_DO_NOT_EXIST")) << std::endl;
}