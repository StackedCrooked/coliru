#include <iostream>
#include <cmath>
#include <vector>

using ullong = unsigned long long;
template <size_t N>
std::vector<ullong> generatePrimes() {
    ullong upperBound = std::ceil(std::sqrt(N));
    bool sieve[N] = {0};
    std::vector<ullong> primes(N/2 + 1);
    ullong insert = 3;
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    for(ullong i = 1; i <= upperBound; ++i) {
        for(ullong j = 1; j <= upperBound; ++j) {
            ullong n = (4*i*i)+(j*j);
            if(n <= upperBound && (n % 12 == 1 || n % 12 == 5))
                sieve[n] = !sieve[n];
            n = (3*i*i)+(j*j);
            if(n <= upperBound && (n % 12 == 7))
                sieve[n] = !sieve[n];
            n = (3*i*i)-(j*j);
            if((i > j) && (n <= upperBound) && (n % 12 == 11)) 
                sieve[n] = !sieve[n];
        }
    }
    for(ullong i = 5; i <= upperBound; ++i) {
        if(sieve[i]) {
            for(ullong j = i*i; j < upperBound; j += i*i)
                sieve[j] = false;
        }
    }
    for(ullong i = 7; i < upperBound; i += 2) {
        if(sieve[i]) {
            primes[insert] = i;
            ++insert;
        }
    }
    return primes;
}

int main() {
    std::vector<ullong> primes = generatePrimes<100>();
    ullong total = 0;
    for(auto& i : primes)
        total += i;
    std::cout << total;
}
