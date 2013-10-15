#include <math.h>
char isPrime (unsigned long number)
{
    if (number <= 1) {
    return 0;
    }
    long double sqrtOfNumber = sqrt(number); // Calculate once.
    for (unsigned long i = 2; i < sqrtOfNumber; i++) {
        if (number%i == 0) { // It has a divisor.
            return 0;
        }
    }
    // Nothing broke us yet....
    return 1;
}

int main()
{
}