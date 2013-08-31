#include <iostream>
#include <string>
#include <iterator>


int main() 
{
    char arr[] = {'T', 'e', 's', 0, 't'};
    std::string s{std::begin(arr), std::end(arr)};
    
    std::cout << s << std::endl;
    std::cout << s.c_str() << std::endl;
}
