#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>
#include <iostream>

int main() 
{
    namespace mp = boost::multiprecision;
    using Int = mp::mpz_int;

    boost::mt19937 rng;
    boost::uniform_int<Int> gen(Int(-1)<<278ul, Int(1)<<500ul);

    std::cout << gen(rng);
}
