#include <iostream>
#include <boost/range/irange.hpp>

using boost::irange;
using std::cout;

int main()
{
    for (auto i : irange(0, 42))
        cout << i << ' ';
}