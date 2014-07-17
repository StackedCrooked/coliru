#include <iostream>

constexpr auto IntegralTime() {
    unsigned long long ret = 0;
    for (auto time = __TIME__; *time; ++time) {
        if (*time != ':') {
            ret *= 10;
            ret += *time - '0';
        }
    }
    
    return ret;
}

int main() {
    std::cout << __TIME__ << ' ' << IntegralTime();
    static_assert(IntegralTime(), "What is __TIME__ doing being 0‽‽‽");
}