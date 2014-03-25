#include <gmpxx.h>
#include <iostream>

int main()
{
    mpz_class u = 1;
    for(unsigned i = 1; i <= 100; ++i)
            u *= i;

    std::cout << "100! = " << u.get_str(10) << '\n';
}