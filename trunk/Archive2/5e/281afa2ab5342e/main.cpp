#include <string>
#include <iostream>

int main()
{
    std::string var {"Cambridge"};
    std::string& r1 {var};
    std::cout << r1 << std::endl;
}
