#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

template<class R>
auto transmogrify(R const& rng)
{
    auto i = 1;
    using Elem = typename R::value_type;
    return rng | boost::adaptors::transformed(
        [&i](Elem const& e) {
        return e * i;
    });
}

int main()
{
    std::vector<int> v = { 2, 3, 5, 7 };
    boost::copy(transmogrify(v), std::ostream_iterator<int>(std::cout, ","));
    std::cout << "\n";
    
    auto i = 1;
    std::transform(begin(v), end(v), begin(v), [&i](int e) { 
        return e * i; 
    });
    for (auto e : v) std::cout << e << ",";
    std::cout << "\n";
}
