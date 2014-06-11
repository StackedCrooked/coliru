#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main(){
    using boost::multiprecision::uint128_t;

    uint128_t mantissa = 1;
    unsigned int binary_exponent = 0;

    std::cout << "0!:\t\t" << mantissa << std::endl;
    std::cout << "1!:\t\t" << mantissa << std::endl;

    for(unsigned i=2; i<257; ++i){
        unsigned tmp = i;
        while (tmp && ((tmp % 2) == 0))
        {
            binary_exponent += 1;
            tmp             /= 2;
        }
        mantissa *= tmp;
        std::cout << i << "!:\t\t" << mantissa << " x 2^" << binary_exponent << std::endl;
    }
}
