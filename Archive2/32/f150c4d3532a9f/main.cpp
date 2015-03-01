#include <iostream>
#include <boost/compressed_pair.hpp>
struct a
{};

struct b : a
{};

int main()
{
    boost::compressed_pair<a, b> p;
    std::cout << sizeof(p) << std::endl;
    
    auto x = p.first();
}