typedef unsigned long long ull;
ull divide(ull dividend, ull divisor) {

    ull denom=divisor;
    ull current = 1;
    ull answer=0;

    if ( denom > dividend)
        return 0;

    if ( denom == dividend)
        return 1;

    while (denom <= dividend) {
        denom <<= 1;
        current <<= 1;
    }

    denom >>= 1;
    current >>= 1;

    while (current!=0) {
        if ( dividend >= denom) {
            dividend -= denom;
            answer |= current;
        }
        current >>= 1;
        denom >>= 1;
    }
    return answer;
}

#include <iostream>

int main() {
    ull imin = 1;
    ull imax = 10000;
    for(ull i=imin; i<imax; ++i) {
        for(ull j=1; j<i; ++j) {
            ull k1 = i/j;
            ull k2 = divide(i,j);
            if (k1 != k2)
                std::cerr << i << " / " << j << " should be " << k1 << " not " << k2 << "\n";
        }
    }
    std::cout << "finished\n";
}