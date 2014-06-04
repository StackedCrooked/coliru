#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


int main()
{
    std::string s = "Hello";
    std::vector<uint8_t> vec(s.begin(), s.end());
    
    std::string s2(vec.begin(), vec.end());
    std::cout << s2 << std::endl;
}
