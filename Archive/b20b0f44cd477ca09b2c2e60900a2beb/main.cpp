#include <string>
#include <algorithm>
#include <iostream>

template<size_t base = 10>
std::string itoa(long long number) {
    static_assert((base >= 2) && (base <= 16), "Invalid base");
    const char digits[] = "0123456789ABCDEF";
    std::string result;
    bool negative = false;
    result.reserve(65);
    unsigned long long copy = 0;
    if(number < 0 && base == 10) {
        copy = -number;
        negative = true;
    }
    else {
        copy = number;
    }
    do {
        result += digits[copy % base];
        copy /= base;
    }
    while(copy);
    if(negative)
        result += '-';
    std::reverse(result.begin(),result.end());
    return result;
}

int main() {
    std::cout << "1234567890 in base 2: " << itoa<2>(1234567890) << '\n';
    std::cout << "in base 8: " << itoa<8>(1234567890) << '\n';
    std::cout << "in base 16: " << itoa<16>(1234567890) << '\n';
    std::cout << "-1234567890 in base 2: " << itoa<2>(-1234567890) << '\n';
    std::cout << "in base 8: " << itoa<8>(-1234567890) << '\n';
    std::cout << "in base 16: " << itoa<16>(-1234567890) << '\n';
}