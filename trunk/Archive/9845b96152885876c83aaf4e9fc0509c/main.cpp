#include <iostream>
#include <set>
#include <cmath>

using ullong = unsigned long long;
ullong nCr(ullong n, ullong k){
    if (k > n) 
        return 0;
    if (k * 2 > n) 
        k = n-k;
    if (k == 0) 
        return 1;

    ullong result = n;
    for(ullong i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

bool isPerfectSquare(ullong n) {
    ullong x = n;
    std::set<ullong> seen;
    std::string str = std::to_string(x);
    for(auto& i : str)
        seen.insert(i - '0');
    while(x*x != n) {
        x = (x + (n/x))/2;
        if(seen.find(x) != seen.end())
            return false;
        seen.insert(x);
    }
    return true;
}

int main() {
    ullong total = 0;
    for(long long x = 0; x <= 5; ++x) {
        for(long long y = 0; y <= 5; ++y) {
            if((isPerfectSquare(y)) && (isPerfectSquare(x)) && (isPerfectSquare(x+y)))
                ++total;
        }
    }
    std::cout << total << "\nnCr: " << nCr(10, 5);
}