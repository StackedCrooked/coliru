#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <iostream>

template <size_t i> void f(){
        std::cout << i << std::endl;
}

struct value_printer
{
    template< typename U > void operator()(U x)
    {
        f<U::value>();
    }
};

int main(){
    using range = boost::mpl::range_c<size_t, 1, 11>;
    
    boost::mpl::for_each<range>(value_printer());
    
    return 0;
}
