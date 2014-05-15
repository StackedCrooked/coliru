#include <boost/range/irange.hpp>

int main()
{
    for (auto i : boost::irange(0, 50) ) {
        std::cout << i << ' ';
    }
}
