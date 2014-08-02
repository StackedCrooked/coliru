#include <iostream>
#include <string>
#include <algorithm>


int main()
{
    std::string s = "ACGTA";
    
    std::cout << "Before: " << s << std::endl;
    
    std::replace(s.begin(), s.end(), 'A', 'T');
    
    std::cout << "After:" << s << std::endl;
}
