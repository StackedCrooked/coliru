#include <vector>
#include <iostream>

template<typename T>
std::vector<T> generatePrimes(unsigned int limit) {
    std::vector<T> primes;
    std::vector<bool> sieve((limit+1)/2);
    if(limit > 1) {
        primes.push_back(2);
        for(unsigned int i = 1, prime = 3; i < sieve.size(); ++i, prime += 2) {
            if(!sieve[i]) {
                primes.push_back(prime);
                for(unsigned int j = (prime*prime)/2; j < sieve.size(); j += prime)
                    sieve[j] = true;
            }
        }
    }
    return primes;
}

int main() {
    std::vector<unsigned> primes = generatePrimes<unsigned>(1000000);
    for(auto& i : primes)
        std::cout << i << '\n';
}