#include <boost/array.hpp>

int main()
{
    boost::array<int, 10> a, b;
    std::copy(a.begin(), a.begin()+10, b.begin()); // asserts ffs
}
