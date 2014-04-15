#include <algorithm>
#include <iterator>
#include <iostream>
#include <boost/iterator/counting_iterator.hpp>

int main() {
    std::array<int, 100> data;
    std::copy(boost::counting_iterator<int>(0), boost::counting_iterator<int>(100), data.begin());
    std::copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, "\n"));
}