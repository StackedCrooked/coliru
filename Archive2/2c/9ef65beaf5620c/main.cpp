#include <iostream>
#include <string>

int main()
{
    const unsigned int a = 123, b = 45678 ;
    
    // http://en.cppreference.com/w/cpp/string/basic_string/to_string
    // http://en.cppreference.com/w/cpp/string/basic_string/stoul
    unsigned long long cat = std::stoull( std::to_string(a) + std::to_string(b) ) ;
    
    std::cout << a << " cat " << b << " => " << cat << '\n' ;
}
