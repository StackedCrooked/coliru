#include <iostream>
#include <string>


using std::string;


template<typename T, unsigned = 0>
struct MultiTON
{
    static T & get() { static T t; return t; }    
};


int main()
{
    MultiTON<string, 0>::get() = "string 0";
    MultiTON<string, 1>::get() = "string 1";
    
    std::cout << MultiTON<string, 0>::get() << std::endl;
    std::cout << MultiTON<string, 1>::get() << std::endl;
}