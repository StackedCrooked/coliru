#include <boost/range/adaptors.hpp>
#include <boost/range/irange.hpp>
#include <boost/phoenix.hpp>
#include <typeinfo>
#include <iostream>

using namespace std;
using namespace boost;
using namespace adaptors;
using namespace phoenix::arg_names;

int main()
{
    for(auto x: irange(0, 10) | transformed( _1 * _1 ) | filtered(_1 % 2))
        cout << x << endl;
}