#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range/iterator_range.hpp>

int main()
{
    std::vector<int> v1{ 1, 2, 3 }, v2{ 6, 4, 2 };

    auto rng = boost::make_iterator_range(
        boost::make_zip_iterator(boost::make_tuple(begin(v1), begin(v2))),
        boost::make_zip_iterator(boost::make_tuple(end(v1), end(v2)))        
    );

    for (auto t : rng)
            std::cout << t.get<0>() << " " << t.get<1>() << "\n";    
}
