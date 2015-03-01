#include <boost/iterator/counting_iterator.hpp>
#include <algorithm>
#include <iostream>

int main()
{
    std::for_each(
        boost::counting_iterator<int>(13),
        boost::counting_iterator<int>(42),
        [](int i){ std::cout << i << ' '; }
    );
}
