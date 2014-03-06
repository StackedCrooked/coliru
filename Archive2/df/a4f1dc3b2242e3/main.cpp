#include <iostream>
#include <string>
 
int main() 
{
    int i = -1;
    std::cout << i % 255 << '\n';
    
    double f = 23.43;
    std::string f_str = std::to_string(f);
    std::cout << f_str << '\n';
}