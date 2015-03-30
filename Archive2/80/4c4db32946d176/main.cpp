#include <boost/math/special_functions/sign.hpp>
#include <iostream>

int main() {
     std::cout << boost::math::copysign(-1234, -1) << std::endl;
}