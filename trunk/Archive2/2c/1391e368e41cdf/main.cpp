#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace boost::multiprecision;

int main()
{
	mpz_int z = 42;
    
    cpp_int i = (z*z*z).convert_to<cpp_int>();
    
    std::cout << i;
}