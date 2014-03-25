#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

unsigned long long powm(boost::multiprecision::cpp_int base, unsigned exp, const unsigned long long mod = 10000000000);

int main()
{
    const int max = 1000;
    boost::multiprecision::cpp_int result = 0;

    for(int i = 1; i <= max; ++i)
    {
        result += powm(i,i);
        result %= 10000000000;
    }

    std::cout << result << std::endl;
}

unsigned long long powm(boost::multiprecision::cpp_int base, unsigned exp, const unsigned long long mod)
{
    boost::multiprecision::cpp_int result = 1;
    while(exp)
    {
        if(exp&1)
        {
            result *= base;
            result %= mod;
        }
        exp >>= 1;
        base *= base;
        base %= mod;
    }
    return static_cast<unsigned long long>(result);
}