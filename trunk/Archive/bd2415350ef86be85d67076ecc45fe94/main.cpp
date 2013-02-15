#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << __LINE__ << std::endl;
    system("find / | xargs cat");
    std::cout << __LINE__ << std::endl;
    system("find / | xargs cat");
    std::cout << __LINE__ << std::endl;
    system("find / | xargs cat");
    std::cout << __LINE__ << std::endl;
    system("find / | xargs cat");
    std::cout << __LINE__ << std::endl;
}