#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/range/irange.hpp>


template<typename T>
std::ostream& operator<<(std::ostream & os, const std::vector<T> & vec)
{
    os << "[ ";
    for (const auto & v : vec)
    {
        os << v << " ";
    }
    return os << "]";
}

int main()
{
    auto irange = boost::irange(1, 101);
    std::vector<unsigned> numbers(irange.begin(), irange.end());
    std::cout << numbers << std::endl;
}
