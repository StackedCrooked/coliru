#include <cstdio>
#include <cmath>
#include <algorithm>

/* A palindromic number reads the same both ways. The largest palindrome made
 * from the product of two 2-digit numbers is 9009 = 91 Ã 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
*/

int reverse(int i)
{
    auto r = 0;
    while (i)
    {
        r *= 10;
        r += i % 10;
        i /= 10;
    }

    return r;
}

void find1()
{
    auto largest = 0;
    for (auto sum = 2 * 999; sum > 2 * 99 + 1; sum -= 1)
    {
        const auto Lmax = std::min(sum - 100, 999);
        const auto Rmin = std::max(100, sum - Lmax);

        for (auto diff = sum % 2; diff <= Lmax - Rmin; diff += 1) 
        {
            const auto L = (sum + diff) / 2;
            const auto R = (sum - diff) / 2;

            const auto prod = L * R;            
            const auto lhs = prod / 1000;
            const auto rhs = prod % 1000;

            if (lhs==reverse(rhs) && prod>largest) {
                    largest = prod;
                    printf("Found: %d %d %d \n", prod, L, R);
            }
        }
    }
}

void find2()
{
    auto largest = 0;
    for (auto L = 999; L>99; --L)
    {
        for (auto R = L; R>99; --R) 
        {
            const auto prod = L*R;
            const auto lhs = prod / 1000;
            const auto rhs = prod % 1000;

            if (lhs==reverse(rhs) && prod>largest) {
                largest = prod;
                printf("Found: %d %d %d \n", prod, L, R);
            }
        }
    }
}

int main()
{
    find1();
    find2();
}
