#include <iostream>
#include <boost/foreach.hpp>

int main()
{
    int a[]{1,2,3,4};
    BOOST_FOREACH(auto b,a)
        ::std::cout << b << ::std::endl;
}