#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

using Int   = boost::multiprecision::cpp_int;
using Float = boost::multiprecision::cpp_dec_float_50;

int main() {
    Int demo("12345678912345678");

    int digits = 0;
    for (Int tmp = abs(demo); tmp > 0; tmp /= 10)
        digits += 1;
    std::cout << digits << ", " << ceil(log10(Float(demo))) << "\n";
}
