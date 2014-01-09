#include <iostream>
#include <stdint.h>


template<typename T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename ...T>
void print_types()
{    
    [](...){}((print_type<T>(), 1)...);
}

int main()
{
    print_types<int32_t, uint32_t, int64_t, uint64_t>();
}