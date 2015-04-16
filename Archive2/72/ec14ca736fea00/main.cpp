// compile option
// g++ -std=c++14
// and clang++ OK

// This program require boost.
// http://www.boost.org/

// boost is c++ full stack library. I use it for rational number

// If you use modern GNU/Linux distribution, you can install by one command. But you must install developer package
// Gentoo: emerge dev-libs/boost
// Ubuntu(I didn't test): sudo apt-get install libboost-all-dev

// If you use Mac OSX, you can goto hell by MacPorts or HomeBrew
// If you use Windows, it run probably by https://cygwin.com/
// I recommend to install Ubuntu on VirtualBox.

#include <bitset>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace mp = boost::multiprecision;

template <typename T>
std::string to_base2(const T n)
{
    int e;
    T m = std::frexp(n, &e);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(std::numeric_limits<T>::digits10 + 1) << m << "*(2^" << e << ")";
    return ss.str();
}

template <typename T>
std::string to_bitset(const T n)
{
    constexpr int bits = sizeof(T) * CHAR_BIT;
    return std::bitset<bits>(*reinterpret_cast<const unsigned long long*>(&n)).to_string().
        insert(bits - std::numeric_limits<T>::digits + 1, 1, ':').
        insert(1, 1, ':');
}

int main(int argc, char** args)
{
    try
    {
        if(argc < 4)
        {
            throw std::runtime_error("usage: float_diff start(rational) increment(rational) end(rational). for instance, ./a.out 0 '1/10' 10");
        }

        mp::cpp_rational rational_n(args[1]);
        const mp::cpp_rational rational_inc(args[2]);
        const mp::cpp_rational rational_last(args[3]);

        double double_n = rational_n.convert_to<double>();
        const double double_inc = rational_inc.convert_to<double>();

        float float_n = rational_n.convert_to<float>();
        const float float_inc = rational_inc.convert_to<float>();

        std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::digits10 + 1);

        std::cout << "{" << std::endl;
        {
            std::cout << "\"increment size\":"                                                                  << std::endl
                      << "{"                                                                                    << std::endl
                      << "\"about\"              : " << rational_inc.convert_to<mp::cpp_dec_float_100>() << "," << std::endl
                      << "\"rational\"           : " << rational_inc                                     << "," << std::endl
                      << "\"double(fixed)\"      : " << double_inc                                       << "," << std::endl
                      << "\"double(science2)\"   : " << to_base2(double_inc)                             << "," << std::endl
                      << "\"double(bitset)\"     : " << to_bitset(double_inc)                            << "," << std::endl
                      << "}"                                                                                    << std::endl;

            std::cout << "\"seq list\":" << std::endl
                      << "["         << std::endl;
            {
                for(; rational_n < rational_last; rational_n += rational_inc, double_n += double_inc, float_n += float_inc)
                {
                    std::cout << "{"                                                                                  << std::endl
                              << "\"about\"              : " << rational_n.convert_to<mp::cpp_dec_float_100>() << "," << std::endl
                              << "\"rational\"           : " << rational_n                                     << "," << std::endl
                              << "\"double(fixed)\"      : " << double_n                                       << "," << std::endl
                              << "\"double(science2)\"   : " << to_base2(double_n)                             << "," << std::endl
                              << "\"double(bitset)\"     : " << to_bitset(double_n)                            << "," << std::endl
                              << "}"                                                                                  << std::endl;
                }
            }
            std::cout << "],"         << std::endl;
        }
        std::cout << "}" << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
