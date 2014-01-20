#include <chrono>
#include <ctime>
#include <iostream>

int triangle(int n)
{
    return ((n + 1) * n) / 2;    
}

// Math fact: a prime decomposition n = Prod_i p_i^e_i yields
// Prod_i (e_i + 1) different divisors
int num_divisors(int n)
{
    auto divisors = 1;  // 1 has one divisor
    {
        auto f = 2;
        auto count = 0;
        while (n % f == 0) {
            ++count;
            n /= f;     // divide by factor of 2
        }
        divisors *= (count + 1);
    }
    
    // <= n guarantees that a prime has 2 divisors
    for (auto f = 3; f <= n; f += 2) {
        auto count = 0;
        while (n % f == 0) {
            ++count;
            n /= f;     // divide by odd factor
        }
        divisors *= (count + 1);
    }
    return divisors;
}

int unique_divisors(int n)
{
    if (n % 2 == 0)
        n /= 2;
    return num_divisors(n);
}

// triangle(n) = (n + 1) * n / 2
// only one of them has a factor of two, and they have no prime factors in common
// we can cache one of the divisor counts while iterating over triangle numbers
int first_triangle_with_more_than_n_divisors(int n)
{
    auto i = 1;
    for (auto f1 = unique_divisors(i), f2 = unique_divisors(i + 1); f1 * f2 <= n; ++i) {
        f1 = f2;                        // re-use result from previous iteration
        f2 = unique_divisors(i + 2);    // only one new computation
    }
    return i;
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    auto const n = 500;
    auto res = first_triangle_with_more_than_n_divisors(n);
    
    std::cout << "the first Triangle number to have over " << n << " divisors : " << triangle(res) << "\n";

    auto stop = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "\nIt took me " << elapsed.count() << " milliseconds." << "\n";
}
