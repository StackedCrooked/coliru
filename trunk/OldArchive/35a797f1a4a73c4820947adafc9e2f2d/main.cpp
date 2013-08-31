/**
 * Problem 10
 * ----------
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 * Find the sum of all the primes below two million.
 */


#include <algorithm>
#include <iostream>
#include <vector>
#include <stdint.h>


bool is_prime(int64_t n, const std::vector<int64_t> & preceding)
{
    // precondition: "preceding" contains all primes < n

    for (auto p : preceding)
    {
        if (n % p == 0)
        {
            return false;
        }
    }
    return true;
}


int64_t next_prime(const std::vector<int64_t> & preceding)
{
    if (preceding.empty())
    {
        return 2;
    }

    if (preceding.back() == 2)
    {
        return 3;
    }

    for (int64_t n = preceding.back() + 2; ; n += 2)
    {
        if (is_prime(n, preceding))
        {
            return n;
        }
    }
}


std::vector<int64_t> get_primes_below(int64_t limit)
{
    std::vector<int64_t> result;
    result.reserve(limit / 2); // no reallocs
    for (;;)
    {
        int64_t next = next_prime(result);
        if (next >= limit)
        {
            return result;
        }
        result.push_back(next);
        if (result.size() % 1000 == 0)
        {
            std::cout << "Found " << result.size() << " primes." << std::endl;
        }
    }
}


int main()
{
    auto primes = get_primes_below(2 * 1000); // should be 2 million!!!
    std::cout << "Found primes: " << primes.size() << std::endl;
    std::cout << std::accumulate(primes.begin(), primes.end(), int64_t()) << std::endl;
}
