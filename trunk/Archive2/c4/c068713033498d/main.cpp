#include <iostream>
#include <iomanip>
#include <ctime>
 
int main()
{
    std::time_t t = std::time(nullptr);
    std::cout << "UTC:   " << std::put_time(std::gmtime(&t), "%c %Z") << '\n';
    std::cout << "local: " << std::put_time(std::localtime(&t), "%c %Z") << '\n';
}