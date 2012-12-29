#include <cmath>
#include <iostream>
#include <vector>
#include <stdint.h>

bool is_prime(uint64_t n, const std::vector<uint64_t> & preceding)
{
    // precondition: "preceding" contains all primes < n
    auto sq = uint64_t(sqrt(n));
    for (auto p : preceding)
    {
        if (p > sq)
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

int main()
{
    std::vector<uint64_t> primes;
    while (primes.size() < 10001)
    {
        primes.push_back(next_prime(primes));
    }
    std::cout << primes.back() << std::endl;
}