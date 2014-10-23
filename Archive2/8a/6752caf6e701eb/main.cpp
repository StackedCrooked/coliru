#include  <sstream>
#include  <string>
#include  <iostream>
#include  <tuple>
#include  <utility>

std::string to_string(std::tuple<int, std::string> int_and_str)
{
    std::stringstream ss;
    ss << "<int(" << std::get<0>(int_and_str) << "), string(" << std::get<1>(int_and_str) << ")>";
    return ss.str();
}

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
     
     std::tuple<int, std::string> int_and_str(4, "hello");
     
     std::cout << to_string(int_and_str) << std::endl;
    
}