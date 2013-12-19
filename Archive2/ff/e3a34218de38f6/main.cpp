#include <iostream>
#include <string>
#include <vector>
#include <thread>

int main()
{
    std::cout << __GNUC__ << std::endl;    
    std::cout << __GNUC_MINOR__ << std::endl;
    std::cout << __GNUC_PATCHLEVEL__ << std::endl;
    return 0;
}
