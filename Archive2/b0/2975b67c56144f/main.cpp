#include <iostream>
#include <stdint.h>


template<typename ...T>
void print_types();


namespace detail {
    template<typename Head, typename ...Tail>
    void print_types_impl(long)
    {    
        print_types<Head>();
        print_types<Tail...>();
    }
    
    template<typename T>
    void print_types_impl(int)
    {    
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
}

template<typename ...T>
void print_types()
{    
    detail::print_types_impl<T...>(0);
}


int main()
{
    print_types<int8_t, int16_t, int32_t, int64_t, uint64_t>();
}
