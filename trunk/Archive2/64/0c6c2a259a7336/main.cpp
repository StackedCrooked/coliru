#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int BigInt;

int main()
{
    BigInt n = 1;
    
    // 30!
    for (int i = 2; i <= 30; ++i)
        n *= i;
        
    std::cout << n << std::endl;
}