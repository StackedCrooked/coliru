#include <iostream>
#include <sstream>

int main()
{
    std::istringstream iss("10:35");
    int hours, minutes;
    char colon;
    iss >> hours >> colon >> minutes;
    std::cout << hours << " : " << minutes;
    
    return 0;
}