#include <iostream>
#include <stdint.h>


// registers a type for something
template<typename T>
void register_type()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<typename ...T>
void register_types()
{    
    int array[] = { (register_type<T>(), 1)... };
    (void)array;
}

int main()
{
    // code duplication
    register_type<char>();
    register_type<short>();
    register_type<int>();
    register_type<long>();
    
    // no code duplication
    register_types<char, short, int, long>();
}