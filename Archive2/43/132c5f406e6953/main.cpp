#include  <sstream>
#include  <string>
#include  <iostream>

template <typename T>
std::string to_string(const T& data)
{
    std::stringstream ss;
    ss << data;
    return ss.str();
}

int main()
{
    
    std::cout << to_string(4) << std::endl;
    
    int i = 4;
    long j = 5;
    short k = 6;
    long long l = 7;
     std::cout << to_string(i) << to_string(j) << to_string(k) << to_string(l)  << std::endl;
    
}