#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << __LINE__ << std::endl;
    system("cat / | xargs grep");
    std::cout << __LINE__ << std::endl;
    system("cat / | xargs grep");
    std::cout << __LINE__ << std::endl;
    system("cat / | xargs grep");
    std::cout << __LINE__ << std::endl;
    system("cat / | xargs grep");
    std::cout << __LINE__ << std::endl;
}