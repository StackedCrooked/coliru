/**
 * Problem 7
 * ---------
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see
 * that the 6th prime is 13.
 *
 * What is the 10001st prime number?
 */


#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdint.h>


bool is_prime(uint64_t n, const std::vector<uint64_t> & preceding)
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
