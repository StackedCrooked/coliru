#include <ctime>
#include <iostream>
 
int main()
{
    std::time_t result = std::time(NULL);
    std::cout << std::asctime(std::localtime(&result));
}