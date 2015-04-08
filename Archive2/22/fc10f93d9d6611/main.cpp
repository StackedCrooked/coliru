#include <boost/multiprecision/gmp.hpp>
#include <iostream>

int main() {
    boost::multiprecision::mpz_int seed = 18446744073709551615ull;
    std::cout << seed;
}
