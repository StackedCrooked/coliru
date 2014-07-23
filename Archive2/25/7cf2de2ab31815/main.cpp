#include <boost/array.hpp>
#include <boost/range.hpp>

int main()
{
    int a[10];
    boost::array<int, 10> b;
    std::copy(boost::begin(a), boost::end(a), &b[0]);
}
