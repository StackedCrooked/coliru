#include <boost/range/irange.hpp>
#include <iostream>

template<class Integer>
decltype(auto) iota(Integer last)
{
    return boost::irange(0, last);    
}

template<class Integer, class StepSize>
decltype(auto) iota(Integer last, StepSize step_size)
{
    return boost::irange(0, last, step_size);    
}

int main(  )
{
    for (auto x : iota(5))
        std::cout << x;
}
