// This is a solution for http://projecteuler.net/problem=4

#include <iostream>

template<typename T>
bool is_palindrome(const T & number) {
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

#include <tuple>

int main() {
    std::tuple<int, int, int> res;
    for (int lhs = 999; lhs >= 100; --lhs) {
        for (int rhs = 999; rhs >= 100 && rhs > lhs; --rhs) {
            const auto product = lhs * rhs;
            if (product > std::get<2>(res) && is_palindrome(product)) {
                res = std::make_tuple(lhs, rhs, product);
            }
        }
    }
    std::cout << std::get<0>(res) << "×" << std::get<1>(res) << "=" << std::get<2>(res);
}