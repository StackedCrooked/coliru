#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    char s[] = "C:\\\0D:\\\0E:\\\0\0";
   
    std::istringstream ss( std::string(s, s + sizeof(s)) );
    
    std::cout << std::vector<std::string>( std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>() ) << " ";
}
