#include <iostream>
#include <algorithm>
#include <string.h>

int wrapcmp(const void* buffer, size_t n, size_t a, size_t b) {
    auto x = (const unsigned char*)buffer;
    auto m = n - std::max(a, b);
    int ret = memcmp(x+a, x+b, m);
    if(ret) return ret;
    auto left = n - m;
    a = (a + m) % n;
    b = (b + m) % n;
    m = left - std::max(a, b);
    ret = memcmp(x+a, x+b, m);
    if(ret) return ret;
    a = (a + m) % n;
    b = (b + m) % n;
    return memcmp(x+a, x+b, left - m);
}

int main() {
    auto x = "Hello World";
    std::cout << wrapcmp(x, strlen(x), 2, 9) << '\n';
}