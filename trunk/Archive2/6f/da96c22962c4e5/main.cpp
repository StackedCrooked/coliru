#include <boost/range/irange.hpp>
#include <iostream>

int main(  )
{
    for (auto x : boost::irange(0, 5))
        std::cout << x;
}
