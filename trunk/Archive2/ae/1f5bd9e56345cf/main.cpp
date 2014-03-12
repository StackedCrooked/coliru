#include <stdio.h>
#include <stdint.h>
#include <math.h>
int main() {
    uint64_t x = 600851475143;
    int sqrtx = sqrt(x);
    uint64_t lfactor = 0;
    uint64_t hfactor = 0;
    for(int i=3; i<sqrtx; i+=2) {
        if(x%i==0)  {
            lfactor=i;
            break;
        }
    }
    hfactor = x/lfactor;
    printf("%llu %llu\n", lfactor, hfactor);
    
}