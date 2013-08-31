#include <iostream>
#include <string>

int main()
{
    std::string toto;
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::cin >> toto;
    std::cout << toto << std::endl;
    return 0;
}