#include <boost/range/irange.hpp>
#include <boost/range/adaptors.hpp>
#include <iostream>

int main()
{
    auto rng = boost::irange(1, 10)
        | boost::adaptors::transformed([](int i) { std::cout << i << ' '; return i * i; });
    auto it = rng.begin();
    it += 6;
    *it; // prints '7'
    it -= 4;
    *it; // prints '3'
}