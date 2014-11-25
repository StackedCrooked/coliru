#include <iostream>
#include <vector>

#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/strided.hpp>

int main()
{
    using boost::adaptors::strided;

    std::vector<int> v = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    auto offset_range = boost::make_iterator_range(v.begin() + 3, v.end());
    auto restamped = offset_range | strided(7);
    
    for(auto const& elem : restamped) std::cout << elem << '\n';
}
