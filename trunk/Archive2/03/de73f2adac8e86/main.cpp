#include <boost/phoenix/phoenix.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/irange.hpp>

#include <iostream>
#include <utility>

using namespace std;
using namespace boost;
using namespace adaptors;
using namespace phoenix::arg_names;


int main()
{
    auto values = irange(-10, 11);
    auto positive = values | filtered(_1 > 0);
    auto doubling = _1 * 2;
    auto result = positive | transformed(doubling);

    auto print = [](auto xs)
    {
        for(auto x : xs)
            std::cout << x << " ";
        cout << endl;
    };
    print(values);
    print(positive);
    print(result);
}
