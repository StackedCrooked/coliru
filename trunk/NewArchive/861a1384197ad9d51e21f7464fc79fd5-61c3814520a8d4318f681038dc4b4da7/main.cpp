#include <iostream>
#include <cassert>
#include <climits>
#include <string>
#include <stdexcept>

unsigned parse(const char* string, unsigned base) {
    static const signed char lut[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, -1, -1, -1, -1
    };
    assert(string);
    assert(*string);
    assert(base>1);
    assert(base<=36);
    unsigned ret = 0;
    while(*string) {
        if (*string > 127) throw std::runtime_error("invalid character");
        signed char n = lut[*string];
        if (n == -1 || n >= base) throw std::runtime_error("invalid character");
        assert((UINT_MAX-n)/base >= ret);
        ret = ret * base + n;
        ++string;
    }
    return ret;
}

std::string serialize(unsigned value, unsigned base) {
    const char* lut = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    assert(base>1);
    assert(base<=36);
    std::string ret;
    ret.reserve(11);
    do {
        assert(value%base<36);
        ret.insert(ret.begin(),lut[value%base]);
        value /= base;
    }while(value>0);
    return ret;
}

int main() {
    assert(parse("X",10)==0);
    std::cout << "pass";
}