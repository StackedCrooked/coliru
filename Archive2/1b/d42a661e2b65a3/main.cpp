#include <iostream>
#include <string>
#include <sstream>


int main()
{
    const int value = 123456789;
    std::stringstream ss;
    ss << value;
    const std::string strValue = ss.str();
    
    auto it = strValue.begin(); 
    int sum = 0;
    
    std::cout << "The digits are: ";
    while(it != strValue.end())
    {
        std::cout << *it << ' ';
        sum += *it - '0';
        ++it;
    }
    std::cout << std::endl << "The sum is: " << sum << std::endl;
}