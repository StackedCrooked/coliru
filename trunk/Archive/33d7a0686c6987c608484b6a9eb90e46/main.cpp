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
    IntSqrt(int64_t n): _number(n) {}

	int64_t operator()() const 
	{
		int64_t remainder = _number;
		if (remainder < 0) { return 0; }

		int64_t place = 1 <<(sizeof(int64_t)*8 -2);

		while (place > remainder) { place /= 4; }

		int64_t root = 0;
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

	int64_t _number;
};


bool is_prime(int64_t n, const std::vector<int64_t> & preceding)
{
	// precondition: "preceding" contains all primes < sqrt(n)
	int64_t square_n = IntSqrt(n)();
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
	}
}


int main()
{
	auto primes = get_primes_below(2 * 1000 * 1000);
	std::cout << std::accumulate(primes.begin(), primes.end(), int64_t()) << std::endl;
} // with time
