#include <boost/multiprecision/gmp.hpp>
#include <cmath>
#include <iostream>

int main() {
    using namespace boost::multiprecision;
    using t = number<gmp_float<1000 * 1000 * 1000>>;
    t n = 1000000000;
    for (t x = 0; x < t(1000) * n; x += n) {
        std::cout << abs(sqrt(x) * sqrt(x) - x) << '\n';
    }
}