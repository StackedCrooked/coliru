#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "boost/serialization/vector.hpp"
#include <algorithm>
#include <set>
#include <iterator>
#include <iostream>
#include <vector>

template <typename Cont>
    std::set<typename std::add_pointer<typename Cont::value_type>::type>
    addresses_of(Cont& input)
{
    std::set<typename std::add_pointer<typename Cont::value_type>::type> s1;

    std::transform(
            input.begin(), input.end(),
            std::inserter(s1, s1.begin()),
            std::addressof<typename Cont::value_type>);

    return s1;
}

int main (void) {

    std::vector<int> data { 1,2,7,4,5 };

    for (auto i : addresses_of(data))
    {
        std::cout << i << ": " << *i << "\n";
    }
}
