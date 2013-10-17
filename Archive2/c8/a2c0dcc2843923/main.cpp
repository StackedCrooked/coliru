#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
 
int main()
{
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() - std::chrono::hours(24));
    
    char buffer[100];
    std::strftime(buffer, 100, "%A %d %B, %Y at %T", std::localtime(&t));
    
    std::cout << buffer << std::endl;
}