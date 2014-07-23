#include <boost/multiprecision/gmp.hpp>

using namespace boost::multiprecision;

struct Integer:
    mpz_int
{
    using mpz_int::mpz_int;
};


int main()
{

}
