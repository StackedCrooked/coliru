/**
 * Problem 006
 * -----------
 * The sum of the squares of the first ten natural numbers is:
 *   1^2 + 2^2 + ... + 10^2 = 385
 *
 * The square of the sum of the first ten natural numbers is:
 *   (1 + 2 + ... + 10)^2 = 55^2 = 3025
 *
 * Hence the difference between the sum of the squares of the first ten natural
 * numbers and the square of the sum is 3025  385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred
 * natural numbers and the square of the sum.
 */


#include <boost/iterator/counting_iterator.hpp>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <stdint.h>


auto sq = [](int64_t v) { return v * v; };


int main()
{
    auto sum_of_sq =
        std::accumulate(boost::make_counting_iterator(1),
                        boost::make_counting_iterator(100 + 1),
                        int64_t(),
                        [](int64_t & x, int64_t n) { x += n*n; return x; });

    auto sq_of_sum =
        sq(std::accumulate(boost::make_counting_iterator(1),
                           boost::make_counting_iterator(100 + 1),
                           int64_t(),
                           [](int64_t & x, int64_t n) { x += n; return x; }));

    std::cout <<  sq_of_sum - sum_of_sq << std::endl;
}
