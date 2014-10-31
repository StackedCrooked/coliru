#include <iostream>
#include <string>
#include <initializer_list>

template <typename T>
void func(T t) 
{
    std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl ;
}

template<typename T, typename... Args>
void func(T t, Args... args) // recursive variadic function
{
    std::cout << __PRETTY_FUNCTION__ << ": " << t <<std::endl ;

    func(args...) ;
}

int main()
{
    std::string
        str1( "Hello" ) ;

    func(1,2.5,'a',str1);
} 