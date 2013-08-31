#include <boost/optional.hpp>
#include <iostream>

template<typename T>
void print_size()
{
    std::cout << sizeof(T) << "\t" << sizeof(boost::optional<T >) << std::endl;
}
    
int main()
{
    print_size<char>();
    print_size<short>();
    print_size<int>();
    print_size<long>();
    print_size<double>();
    print_size<long double>();
}