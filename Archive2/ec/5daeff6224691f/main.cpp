#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>
#include <iostream>

int main() 
{
    namespace mp = boost::multiprecision;
    using Int = mp::mpz_int;

    boost::mt19937 rng(3);
    boost::uniform_int<Int> gen(-pow(Int(2), 400), pow(Int(2), 400));

    for (int i=0; i<10; ++i)
        std::cout << gen(rng) << "\n";
}
