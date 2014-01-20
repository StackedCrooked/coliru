#include <iostream>
#include <string.h>

int main()
{
    double OverallVolume = 1535625179.1619387;
    char buffer[255];
    sprintf(buffer, "%e", OverallVolume);
    std::cout << buffer << std::endl;
    
    
    sprintf(buffer, "%.7e", OverallVolume);
    std::cout << buffer << std::endl;
}
