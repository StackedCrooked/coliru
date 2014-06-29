// This is a solution for http://projecteuler.net/problem=4

#include <cmath>
#include <iostream>
#include <tuple>
#include <type_traits>

template<typename T>
bool is_palindrome(T number) {
    static_assert(std::is_integral<T>::value, "T can only be integral");
    T remainder = number;
    const T size = number == 0 ? 1 : std::log10(number) + 1;
    const auto half_size = size / 2 + 1;
    for (int i = 0; i < half_size; ++i) {
        const T offset = std::pow(10, size - i - 1);
        const T first_digit = number / offset;//get first decimal digit
        number %= offset;//discard first decimal digit
        
        const T last_digit = remainder % 10;//get last decimal digit
        remainder /= 10;//discard last decimal digit
        
        if (first_digit != last_digit) {
            return false;
        }
    }
    return true;
}

template<typename T>
constexpr bool is_palindrome2(const T & number) {
    static_assert(std::is_integral<T>::value, "T can only be integral");
    T remainder = number;
    T reverse = 0;
    while (remainder > 0) {
        const T digit = remainder % 10;//get last decimal bit
        remainder /= 10;//discard last decimal bit
        reverse *= 10;//shift
        reverse += digit;//append
    }
    return reverse == number;
}

template<typename T>
bool is_palindrome3(const T & number) {
    static_assert(std::is_integral<T>::value, "T can only be integral");
    T remainder = number;
    T reverse = 0;
    const T size = number == 0 ? 1 : std::log10(number) + 1;
    const auto half_size = size / 2;
    const T max = half_size + size % 2;
    for (int i = 0; i < max; ++i) {
        const T digit = remainder % 10;//get last decimal bit
        remainder /= 10;//discard last decimal bit
        reverse *= 10;//shift
        reverse += digit;//append
    }
    const T cutoff = number / std::pow(10, half_size);
    return reverse == cutoff;//just compare the first half with the last half reversed
}

template<typename T>
constexpr std::tuple<T, T, T> largest_square_palindrome(const T & max) {
    static_assert(std::is_integral<T>::value, "T can only be integral");
    T one = 0;
    T two = 0;
    T res = 0;
    for (T lhs = max; lhs * max > res; --lhs) {
        for (T rhs = max; rhs > lhs; --rhs) {
            const auto product = lhs * rhs;
            if (product > res && is_palindrome2(product)) {
                one = lhs;
                two = rhs;
                res = product;
            }
        }
    }
    return std::make_tuple(res, one, two);
}

int main() {
    constexpr const auto res = largest_square_palindrome(999);
    std::cout << std::get<2>(res) << "×" << std::get<1>(res) << "=" << std::get<0>(res) << std::endl;
}