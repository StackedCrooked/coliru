#include <boost/optional.hpp>
#include <iostream>

template<typename T>
void print_size()
{
    std::cout << sizeof(T) << "\t" << sizeof(boost::optional<T >) << std::endl;
}
    
int main()
{
    std::cout << "Ignore the zero: " << __COUNTER__ << std::endl;
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
    print_size<char[__COUNTER__]>();
}