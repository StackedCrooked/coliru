#include <stdio.h>
#include <math.h>

/* A palindromic number reads the same both ways. The largest palindrome made
 * from the product of two 2-digit numbers is 9009 = 91 × 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
*/

unsigned reverse(unsigned i)
{
    unsigned r = 0;
    while (i)
    {
        r *= 10;
        r += i % 10;
        i /= 10;
    }

    return r;
}

int main()
{
    unsigned largest = 0;
    for (unsigned j = 999; j>99; --j)
    {
        for (unsigned k = j; k>99; --k) 
        {
            const unsigned prod = j*k;

            if (prod < 100000)
                break;
            
            const unsigned lhs = prod / 1000;
            const unsigned rhs = prod % 1000;

            if (lhs==reverse(rhs))
            {
                //printf("%d (%d x %d)\n", prod, j, k);
                if (prod>largest)
                    largest = prod;
            }
        }
    }

    printf("%d\n", largest);
    return 0;
}
