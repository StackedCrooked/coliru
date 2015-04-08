#include <cstdint>

uint32_t pow2(uint32_t x) {
    return x * x;
}

uint32_t nthdigit(uint32_t x, uint32_t n) {
    static uint32_t pow10[] = {
        100000000,
        10000000,
        1000000,
        100000,
        10000,
        1000,
        100,
        10,
        1
    };

    return (x / pow10[n]) % 10;
}

uint32_t number_of_digits(uint32_t digit) noexcept {
    uint32_t digits = 1;
    if(digit >= 100000000) {
        // in basic_decimal no number can be greater than 999,999,999
        return 9;
    }

    // unrolled loop based on pow-of-two
    if(digit >= 10000) {
        digit /= 10000;
        digits += 4;
    }
    if(digit >= 100) {
        digit /= 100;
        digits += 2;
    }
    if(digit >= 10) {
        digit /= 10;
        digits += 1;
    }
    return digits;
}

#include <iostream>

int main() {
    uint32_t x = 123456789;
    auto end = number_of_digits(x);
    std::cout << end << '\n';
    uint32_t sum = 0;
    for(unsigned i = 0; i < end; ++i) {
        std::cout << nthdigit(x, i) << '\n';
        sum += pow2(nthdigit(x, i));
    }
    std::cout << sum << '\n';
}


