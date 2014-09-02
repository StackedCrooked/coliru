#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

int main()
{
    {
        mp::cpp_int a, b;
        auto c = a % b;
    }
    {
        mp::number<mp::cpp_dec_float<128>> a, b;
        //auto c = a % b; // error
    }
}
