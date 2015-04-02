#include <iostream>

int nth_jeffrey_number(int n) {
    if (n == 0) return 3;
    if (n == 1) return 5;
    
    if ((n & 2) == 0) return nth_jeffrey_number(n / 4 - 1) * 3;
    if ((n & 2) == 1) return nth_jeffrey_number(n / 4 - 1) * 5;
    if ((n & 2) == 2) return nth_jeffrey_number(n / 4) * 3;
    if ((n & 2) == 3) return nth_jeffrey_number(n / 4) * 5;
}


int main() {
    for (int i = 0; i < 500; ++i) {
        std::cout << nth_jeffrey_number(i) << ' ';
    }
}
