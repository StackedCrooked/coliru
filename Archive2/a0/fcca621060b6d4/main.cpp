#include <iostream>

int nth_jeffrey_number(int n) {
    if (n == 0) return 1;
    
    return (((n - 1) & 1) == 0)
        ? nth_jeffrey_number(n / 2) * 3
        : nth_jeffrey_number(n / 2 - 1) * 5;
}


int main() {
    for (int i = 0; i < 500; ++i) {
        std::cout << nth_jeffrey_number(i) << ' ';
    }
}
