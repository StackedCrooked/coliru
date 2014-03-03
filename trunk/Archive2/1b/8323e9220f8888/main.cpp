#include <iostream>
#include <iterator>
#include <vector>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range/iterator_range.hpp>

template<class... Ranges>
auto combine(Ranges const&... ranges) 
// add -> decltype( boost::make_iterator_range(...) ) in C++11
{
    return boost::make_iterator_range(
        boost::make_zip_iterator(boost::make_tuple(begin(ranges)...)),
        boost::make_zip_iterator(boost::make_tuple(end(ranges)...))        
    );
}

int main()
{
    std::vector<int> v1{ 1, 2, 3 }, v2{ 6, 4, 2 };
    
    for (auto&& t : combine(v1, v2))
            std::cout << t.get<0>() << " " << t.get<1>() << "\n";    
}
