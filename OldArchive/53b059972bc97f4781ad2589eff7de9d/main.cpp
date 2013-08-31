#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <chrono>

class Stopwatch {
public:
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start;
    Stopwatch(): start(Clock::now()) {}
    void elapsed() {
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms\n";
    }
    void reset() {
        start = Clock::now();
    }
};

void printformat(const char* str) {
    while(*str) {
        if(*str == '%' && *(++str) != '%')
            throw std::runtime_error("Missing arguments");
        std::cout << *str++;
    }
}

template<typename T, typename... Args>
void printformat(const char* str, T value, Args... args) {
    while(*str) {
        if(*str == '%' && *(++str) != '%') {
            std::cout << value;
            printformat(str,args...);
            return;
        }
        std::cout << *str++;
    }
    throw std::logic_error("Too many arguments");
}

template<size_t base = 10>
std::string itoa(long long number) {
    static_assert((base >= 2) && (base <= 16), "Invalid base");
    const char digits[] = "0123456789ABCDEF";
    std::string result;
    bool negative = false;
    result.reserve(65);
    if(number < 0 && base == 10) {
        number = -number;
        negative = true;
    }
    unsigned long long copy = number;
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
    Stopwatch k;
    printformat("12974128127129129 in base 2: %, base 8: %, base 16: %",itoa<2>(12974128127129129),itoa<8>(12974128127129129),itoa<16>(12974128127129129));
    printformat("\n-12974128127129129 in base 2: %, base 8: %, base 16: % \n",itoa<2>(-12974128127129129),itoa<8>(-12974128127129129), itoa<16>(-12974128127129129));
    k.elapsed();
}

