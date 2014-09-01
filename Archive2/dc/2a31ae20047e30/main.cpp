#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/strong_typedef.hpp>
#include <iostream>

namespace XX {
    BOOST_STRONG_TYPEDEF(boost::multiprecision::number<boost::multiprecision::mpz_int>, Integer);

	std::ostream& operator<<(std::ostream& os, Integer const&) {
		return os << "XX overload";
	}
}

using namespace boost::multiprecision;

int main()
{
	number<mpz_int> a("-123789463276540234876");
	XX::Integer b(a);

	std::cout << a << "\n";
	std::cout << b << "\n";
}
