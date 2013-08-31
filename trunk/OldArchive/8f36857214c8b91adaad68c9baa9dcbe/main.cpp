/**
 * Problem 10
 * ----------
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 * Find the sum of all the primes below two million.
 */


#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <stdint.h>


bool is_prime(uint64_t n, const std::vector<uint64_t> & preceding)
{
    // precondition: "preceding" contains all primes < sqrt(n)

    uint64_t square_n = static_cast<uint64_t>(std::sqrt(n));
    for (auto p : preceding)
    {
        if (p > square_n)
        {
            return true;
        }

        if (n % p == 0)
        {
            return false;
        }
    }
    return true;
}


uint64_t next_prime(const std::vector<uint64_t> & preceding)
{
    if (preceding.empty())
    {
        return 2;
    }

    if (preceding.back() == 2)
    {
        return 3;
    }

    for (uint64_t n = preceding.back() + 2; ; n += 2)
    {
        if (is_prime(n, preceding))
        {
            return n;
        }
    }
}


std::vector<uint64_t> get_primes_below(uint64_t limit)
{
    std::vector<uint64_t> result;
    result.reserve(limit / 2); // no reallocs
    for (;;)
    {
        uint64_t next = next_prime(result);
        if (next >= limit)
        {
            return result;
        }
        result.push_back(next);
    }
}


int main()
{
    auto primes = get_primes_below(2 * 1000 * 1000);
    std::cout << std::accumulate(primes.begin(), primes.end(), uint64_t()) << std::endl;
} // with time