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


struct IntSqrt
{
  IntSqrt(int n): _number(n) {}

  int operator()() const 
  {
    int remainder = _number;
    if (remainder < 0) { return 0; }

    int place = 1 <<(sizeof(int)*8 -2);

    while (place > remainder) { place /= 4; }

    int root = 0;
    while (place)
    {
      if (remainder >= root + place)
      {
        remainder -= root + place;
        root += place*2;
      }
      root /= 2;
      place /= 4;
    }
    return root;
  }
  
  int _number;
};


bool is_prime(uint64_t n, const std::vector<uint64_t> & preceding)
{
    // precondition: "preceding" contains all primes < sqrt(n)
    uint64_t square_n = IntSqrt(n)();
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