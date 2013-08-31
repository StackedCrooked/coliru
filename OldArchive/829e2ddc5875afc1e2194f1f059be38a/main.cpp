#include <chrono>
#include <bitset>
#include <vector>
#include <iostream>

using ullong = unsigned long long;

class Stopwatch {
public:
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start;
    Stopwatch(): start(Clock::now()) {}
    ~Stopwatch() {
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms";
    }
};

template<typename T, size_t limit>
std::vector<T> generatePrimes2() {
    std::vector<T> primes;
    std::bitset<limit> sieve;
    sieve.set(0);
    sieve.set(1);
    for(ullong i = 2; i < limit; ++i) {
        if(sieve[i] == false) {
            primes.push_back(i);
            for(ullong j = 2*i; j < limit; j += i)
                sieve.set(j);
        }
    }
    return primes;
}

int main() {
    std::cout << "Generating 35m primes..\n";
    Stopwatch w;
    std::vector<unsigned> primes = generatePrimes2<unsigned,35000000>();
}