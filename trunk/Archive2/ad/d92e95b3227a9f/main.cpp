#include <cstdint>
#include <cmath>
#include <string>
#include <limits>
#include <cstdlib>
#include <stdexcept>

constexpr bool is_digit(char c) noexcept {
    return c >= '0' && c <= '9';
}

template<typename T>
constexpr T from_char(char c, const T& val) noexcept {
    return (c - '0') + val * 10;
}

struct decimal {
public:
    decimal() noexcept = default;
    decimal(int64_t value, int32_t exponent) noexcept: value(value), exponent(exponent) {}
    decimal(const char* str, size_t length) {
        if(length == 0 || str == nullptr) {
            return;
        }
        // format is:
        // [sign]value[.digits][[e|E][sign][exponent]]

        // [sign]
        size_t i = 0;
        if(str[i] == '-') {
            value = -1;
            ++i;
        }
        else if(str[i] == '+') {
            value = 0;
            ++i;
        }
        else if(is_digit(str[i])) {
            value = from_char(str[i++], value);
        }
        else {
            throw std::invalid_argument("decimal::decimal: invalid first character: must be a digit or +/-");
        }

        // value
        for(; i < length; ) {
            if(is_digit(str[i])) {
                value = from_char(str[i++], value);
            }
            else if(str[i] == '.') {
                ++i;
                // [.digits]
                handle_digits(str, i, length);
                return;
            }
            else if(str[i] == 'e' || str[i] == 'E') {
                ++i;
                // [[e|E][sign][exponent]]
                handle_exponent(str, i, length);
                return;
            }
            else {
                throw std::invalid_argument("decimal::decimal: format must be [sign]value[.digits][[e|E][sign][exponent]]");
            }
        }
    }

    explicit decimal(const char* str): decimal(str, std::char_traits<char>::length(str)) {}
    explicit decimal(const std::string& str): decimal(str.c_str(), str.size()) {}
// private:
    // values are stored internally as:
    // decimal = value * 10 ^ exponent
    // 64-bits of value, 32 bits of exponent
    int64_t value = 0;
    int32_t exponent = 0;

    void handle_digits(const char* str, size_t i, size_t length) {
        // [.digits]
        for(; i < length; ) {
            if(is_digit(str[i])) {
                value = from_char(str[i++], value);
                --exponent;
            }
            else if(str[i] == 'e' || str[i] == 'E') {
                ++i;
                return handle_exponent(str, i, length);
            }
            else {
                throw std::invalid_argument("decimal::decimal: format must be [sign]value[.digits][[e|E][sign][exponent]]");
            }
        }
    }

    void handle_exponent(const char* str, size_t i, size_t length) {
        // [[e|E][sign][exponent]]
        // i should point to a valid character
        if(i >= length) {
            throw std::invalid_argument("decimal::decimal: unexpected end of string found");
        }

        bool negative = false;
        int32_t exp = 0;
        // check the sign, [sign]
        if(str[i] == '-') {
            negative = true;
            ++i;
        }
        else if(str[i] == '+') {
            ++i;
        }
        else if(is_digit(str[i])) {
            exp = from_char(str[i++], exp);
        }
        else {
            throw std::invalid_argument("decimal::decimal: format must be [sign]value[.digits][[e|E][sign][exponent]]");
        }

        // the actual [exponent] bit
        for(; i < length; ) {
            if(is_digit(str[i])) {
                exp = from_char(str[i++], exp);
            }
            else {
                throw std::invalid_argument("decimal::decimal: format must be [sign]value[.digits][[e|E][sign][exponent]]");
            }
        }

        exponent += negative ? -exp : exp;
    }

};

// 1.234e+10 => { value: 1234, exponent: 7 }
// 1.234e-10 => { value: 1234, exponent: -13 }

#include <iostream>

int main() {
    decimal x("1.234e-10");
    std::cout << x.value << ' ' << x.exponent << '\n';
    decimal y("1.234e+10");
    std::cout << y.value << ' ' << y.exponent << '\n';
}
