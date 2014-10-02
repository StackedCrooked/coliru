#include <ctime>
#include <iostream>
 
int main()
{
    int result = std::time(nullptr);
    std::cout <<  result << " seconds since the Epoch\n";
}