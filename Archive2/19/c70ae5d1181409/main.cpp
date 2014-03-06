//find largest prime factor for x <2^64
#include <stdio.h>
#include <stdint.h>
#include <math.h>
int main() {
    uint64_t x = 600851475143;
    x = 125;
    int wheel[] = {4,2,4,2,4,6,2,6};
    while(x>2 && x%2==0) x/=2;
    while(x>3 && x%3==0) x/=3;
    while(x>5 && x%5==0) x/=5;   
    int j=0;
    for(uint64_t i=7; i<=sqrt(x); i+=wheel[j++%8]) {
        while(x>i && x%i==0) x/=i;
    }
    printf("%llu\n", x);
}