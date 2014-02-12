#include <iostream>

unsigned long getSumDivisors(const unsigned long number) {
    unsigned long sum = 0;
    for(unsigned long i = 0; i < number; ++ i) {
        if(number % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    std::cout << getSumDivisors(5);
    return 0;
}