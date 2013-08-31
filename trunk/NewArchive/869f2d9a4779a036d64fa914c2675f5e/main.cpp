#include <iostream>
#include <cmath>

bool isPrime(int n) {
    if(n == 1)
        return false;
    else if(n < 4.0)
        return true;
    else if(n % 2 == 0)
        return false;
    else if(n < 9)
        return true;
    else if (n % 3 == 0)
        return false;
    else {
        int r = floor(sqrt(static_cast<double>(n)));
        int f = 5;
        while (f <= r) {
            if (n % f == 0) {
                return false;
                 }
            if (n % (f+2) == 0) {
                return false;
                }
            f = f+6;
        }
    return true;
    }

}

int main() {
    size_t total = 1;
    for(int i = 3; i < 140000; i++) {
        if(isPrime(i))
            ++total;
        if(total == 10001) {
            std::cout << i << "\n";
            break;
        }
    }
}