#include <boost/math/special_functions/sign.hpp>
#include <iostream>
#include <cstdint>

int main() {
    int64_t value = -5000;
    int64_t sign = -1;
    
     std::cout << boost::math::copysign(value, sign) << std::endl;
}

