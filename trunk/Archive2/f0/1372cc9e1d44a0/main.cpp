#include <iostream>
#include <type_traits>

template<int x, int y>
    void stuff(std::string arg1, std::string arg2)
    { 
        std::cout << "woo\n";
    }
    
template<int x, int y>
    template std::enable_if<(x == y), void>::type stuff(std::string arg1, std::string arg2)
    { /* sfinae */ }


int main(void)
{
    stuff<1,2>("hello", "world");
}