#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <iterator>

//#define NDEBUG        // release build disables assert and debug prints
#include <cassert>

template<typename T>
T pow2(unsigned char n)
{
    // since unsigned it cannot be lesser than 0, so it's ok to check only for the upper limit
    assert(n <= (std::numeric_limits<T>::digits) - 1);
    T v{1u};
    return v << n;
}

int get_binary_digit(char ch)
{
    const std::string err = "Invalid binary digit " + std::string(1, ch);
    return (ch == '1') ? 1 : (ch == '0') ? 0 : throw std::invalid_argument(err);
}

template <typename T>
T int_bin2dec(const std::string &str_integral)
{
    signed power = 0;
    const T integral = std::accumulate(str_integral.crbegin(), str_integral.crend(), T{},
    [&](T accum, char ch)
    {
        const auto digit = get_binary_digit(ch);
#ifndef NDEBUG
        std::cout << power << '\t' << pow2<T>(power) << std::endl;
#endif
        return accum + (digit * pow2<T>(power++));
    });
    return integral;
}

template <typename T>
void fract_bin2dec(const std::string &str_fraction,
                   T &num,
                   T &den)
{
    num = 0, den = 1;
    signed power = -1;
    for_each(str_fraction.cbegin(), str_fraction.cend(), [&](char ch)
    {
        const auto numerator = get_binary_digit(ch);
        if(numerator)
        {
            const auto denominator = pow2<T>(-power);
            const auto scalar = denominator / den;
            num = (num * scalar) + 1;
            den = denominator;
#ifndef NDEBUG
        std::cout << power << "\t 1/" << denominator << '\t' << num << " / " << den << std::endl;
#endif
        }
        --power;
    });
}

template <typename T>
void print_fraction(bool negative,
                    T integral,
                    T num,
                    T den)
{
    if (negative) std::cout << "-[";
    if (integral) std::cout << integral << " + (";
    std::cout << num
              << " / "
              << den;
    if (integral) std::cout << ")";
    if (negative) std::cout << "]";
}

template <typename fraction_type, typename T>
void print_real(bool negative,
                T integral,
                T num,
                T den)
{
    if (negative) std::cout << "-";
    std::cout << std::setprecision(std::numeric_limits<fraction_type>::digits10)
              << (integral + (num / static_cast<fraction_type>(den)))
              << std::endl;
}

// usage: bin2rational 0.000110011001100110011001101
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Insufficient data" << std::endl;
        std::cerr << "Usage: bin2rational <fractional binary number>" << std::endl;
        return -1;
    }

    auto const *binary = argv[1];
    const bool negative = ('-' == *binary);
    binary += negative ? 1 : 0;

    std::stringstream ss{binary};
    std::string int_part, fract_part;
    if(getline(ss, int_part, '.'))
    {
        if(getline(ss, fract_part, '.'))
        {
            std::string dummy;
            if(getline(ss, dummy, '.'))
                std::cerr << "Invalid format!" << std::endl;
        }
    }

    using integer_type = unsigned long long;
    const auto integral = int_bin2dec<integer_type>(int_part);
    integer_type num = {}, den = {};
    fract_bin2dec(fract_part, num, den);

    if(integral || num)
    {
        print_fraction(negative, integral, num, den);
        std::cout << " = ";
        print_real<long double>(negative, integral, num, den);
    }
    else
        std::cout << "0" << std::endl;
}
