#include <iostream>
#include <algorithm>
#include <boost/iterator/filter_iterator.hpp>

struct is_prime
{
    bool operator()(int n) const
    {
        int small_primes[] = { 2, 3, 5, 7, 11, 13, 17, 19 };
        return std::all_of(std::begin(small_primes), std::end(small_primes), [=](int const& p) {
            return n == p || n % p != 0;
        });
    }    
};

int main() 
{
    int numbers[] = { 24, 12, 7, 8, 11, 95, 47 };
    auto pb = boost::make_filter_iterator(is_prime{}, std::begin(numbers), std::end(numbers));
    auto pe = boost::make_filter_iterator(is_prime{}, std::end(numbers), std::end(numbers));
    
    auto result = std::minmax_element(pb, pe);
    std::cout << *(result.first.base()) << " " << *(result.second.base());
}