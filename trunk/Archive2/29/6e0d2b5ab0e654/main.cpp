#include <boost/array.hpp>

int main()
{
    boost::array<int, 10> a, b;
    std::copy(&a[0], &a[10], &b[0]); // asserts ffs
}
