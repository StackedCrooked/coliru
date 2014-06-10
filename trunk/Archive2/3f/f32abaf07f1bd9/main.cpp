#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main(){
    using boost::multiprecision::cpp_int;
    using boost::multiprecision::cpp_rational;

    cpp_rational r(1);
    r /= (cpp_int(1)<<127);

    std::cout << "0!:\t\t" << r << std::endl;
    std::cout << "1!:\t\t" << r << std::endl;

    for(cpp_rational i=2; i<257; ++i){
        r *= i;
        std::cout << i << "!:\t\t" << r << std::endl;
    }
}
