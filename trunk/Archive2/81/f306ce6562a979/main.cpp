#include <iostream>
#include <iterator>
#include <vector>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

template<class R>
auto delta_beg(R const& rng1, R const& rng2)
{
    using Elem = typename R::value_type;
    return rng1 | boost::adaptors::transformed(
        [first2 = begin(rng2)](Elem const& e) {
        return e - *first2;
    });
}

template<class R>
auto delta_rng(R const& rng1, R const& rng2)
{
    using Elem = typename R::value_type;
    return rng1 | boost::adaptors::transformed(
        [first2 = begin(rng2)](Elem const& e) mutable {
        return e - *first2++;
    });
}

int main()
{
    auto r1 = std::vector<int>{ 8, 10, 12, 15 };
    auto r2 = std::vector<int>{ 1,  2,  9, 13 };

    // prints 7, 9, 11, 14
    boost::copy(delta_beg(r1, r2), std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";
    
    // ERROR, should print 7, 8, 3, 2
    boost::copy(delta_rng(r1, r2), std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";
}
