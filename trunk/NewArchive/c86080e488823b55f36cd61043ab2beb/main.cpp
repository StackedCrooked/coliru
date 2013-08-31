#include <bitset>
#include <iostream>

int main () {
    using ulong = unsigned long long;
    ulong sum = 0;
    ulong j = 0;
    const ulong bound = 2000000;
    std::bitset<bound> sieve;
    sieve.set(0);
    sieve.set(1);
    for (ulong i = 2; i < bound; ++i)
    {
        if (sieve[i] == false) { 
            sum += i;
            for (j = 2*i; j < bound; j += i) {
                sieve.set(j);
            }
        }
    }
    std::cout << sum;
} // with time22