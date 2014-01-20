#include <iostream>
#include <string>
#include <cmath>

int main() {
    int solution = 0;
    
    std::string forward;
    std::string current;
    int next;
    int count;
    
    const int sieveSize = 1000000;
    const int primeSize = 100000;
    
    bool sieve[sieveSize];
    long long primes[primeSize];
    
    //Sieve - Default the first 2
    sieve[0] = true;
    sieve[1] = true;
    int counter = 0;
    
    for (int i = 2; i < sieveSize; i++) {
        if (sieve[i]) {
            continue;
        }
        primes[counter] = i;
        
        for (int j = i + i; j < sieveSize; j = j + i) {
            sieve[j] = true;
        }
        counter++;
    }
    
    
    //Replace
    for (int i = 0; i < primeSize; i++) {
        current = std::to_string(primes[i]);
    
        for (int j = 0; j < current.size(); j++) {
            for (int k = j + 1; k < current.size(); k++) {
                if (current[j] != current[k]) {
                    continue;
                }
                
                for (int l = k + 1; l < current.size(); l++) {
                    if (current[k] != current[l]) {
                        continue;
                    }
                    
                    //Iterate digits
                    count = 0;
                    for (int digit = 0; digit <= 9; digit++) {
                        forward = current;
                        
                        forward[j] = digit + '0';
                        forward[k] = digit + '0';
                        forward[l] = digit + '0';
                        
                        if (forward[0] != '0') {
                            next = std::stoll(forward);
    
                            if (!sieve[next] && next < sieveSize) {
                                count++;
                            }
                        }
                    }
                    
                    //Found it
                    if (count == 8 && solution == 0) {
                        solution = primes[i];
                        break;
                    }
                }
            }
        }
    }
    
    std::cout << "Solution: " << solution << std::endl;
}