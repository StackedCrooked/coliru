#include <boost/multiprecision/gmp.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

int main() {
    mp::mpz_int n;
    std::cin >> n;
    n = n*2;
    std::cout << n << "\n";
}
