#include <boost/array.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/include/io.hpp>
#include <iostream>

int main()
{
    using namespace boost;

    boost::array<int, 4> iv4 { 1,2,3,4 };
    boost::array<double, 4> id4 { .1, .2, .3, .4 };

    auto r = fusion::transform(iv4, id4, [](auto a, auto b) { return a+b; });
    std::cout << r;
}

