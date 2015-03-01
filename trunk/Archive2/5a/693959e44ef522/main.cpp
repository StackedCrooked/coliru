#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/irange.hpp>
#include <boost/iterator/counting_iterator.hpp>

#include <algorithm>
#include <iostream>

int main()
{
    boost::for_each(boost::irange(13, 42), [](int i){ std::cout << i << ' '; });
    std::cout << std::endl;
    
    std::for_each(boost::make_counting_iterator(13),
                  boost::make_counting_iterator(42), 
                  [](int i){ std::cout << i << ' '; });
    std::cout << std::endl;
}
