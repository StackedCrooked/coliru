#include <iostream>
#include <utility>

constexpr const char* foo(double d)
{
    return 
      (d == 1.0) ? "Apple" 
    : (d == 2.0) ? "Pear" 
    : (d == 3.0) ? "Orange" 
    : "";
}

int main()
{
    std::string s = foo(3.0);
    std::string s2 = foo(4.0);
    
    std::cout << s << " " << s2 << std::endl;
    return 0;
}