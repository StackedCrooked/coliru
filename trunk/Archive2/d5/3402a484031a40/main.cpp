#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>

int main()
{
    char const* foo1 = "Hello ", *foo2 = "World";
    
    boost::format f("Text: %s");
    
    f % foo1 % foo2;
    
    std::cout << str(f) << std::endl;
}
