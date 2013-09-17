/*
 * The sum of the squares of the first ten natural numbers is,
 * 1² + 2² + ... + 10² = 385
 *
 * The square of the sum of the first ten natural numbers is,
 * (1 + 2 + ... + 10)² = 552 = 3025
 *
 * Hence the difference between the sum of the squares of the first ten natural
 * numbers and the square of the sum is 3025 - 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
 */

using ulong = unsigned long;

static constexpr inline ulong series(ulong n) 
{ 
    return ((n+1)*n)/2; 
}

#include <iostream>

constexpr auto N = 100ul;

int main()
{
    auto square_of_sum = series(N) * series(N); // fullly compile-time

    auto sum_of_squares = 0ul;
    auto i = 1ul, j = N;

    while (i<j)
    {
        sum_of_squares += (i+j)*(i+j) - 2*(i*j);
        i++, --j;
    }

    if (i==j)
        sum_of_squares += i*i;

    std::cout << square_of_sum - sum_of_squares;
}
