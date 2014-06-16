#include <iterator>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/reversed.hpp>

int main()
{
    std::vector<int> vec(20);
    std::iota(vec.begin(), vec.end(), 0);
    
    using namespace boost::adaptors;
    
    for(auto i : vec | filtered([](int i){ return i % 2 == 0; })
                     | transformed([](int i){ return i * 2; })
                     | reversed) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}
