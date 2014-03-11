#include <boost/multi_array.hpp>

using Arr = boost::multi_array<int, 3>;

struct Ok { };
struct NotOk : boost::noncopyable { };

int main()
{
    boost::multi_array<int,   3> arr1(boost::extents[7][6][3]); // ok
    boost::multi_array<Ok,    3> arr2(boost::extents[7][6][3]); // ok
    boost::multi_array<NotOk, 3> arr3(boost::extents[7][6][3]); // COMPILE ERROR
}
