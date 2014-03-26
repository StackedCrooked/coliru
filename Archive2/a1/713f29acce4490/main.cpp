#include<iostream>
#include<cmath>

unsigned phi(unsigned long x) {
    unsigned ret = 1;
    unsigned pow;
    
    for (unsigned i = 2; x != 1; i++) {
        pow = 1;
        while (!(x % i)) {
            x /= i;
            pow *= i;
        }
        ret *= (pow - (pow/i));
    }
    return ret;
}

int main() {
    unsigned long long solution = 0;
    for (int n = 0; n < 10000; n++) {
        std::cout << n << ", ";
        solution += phi(n);
    }
    std::cout << "Solution: " << solution << std::endl;
}