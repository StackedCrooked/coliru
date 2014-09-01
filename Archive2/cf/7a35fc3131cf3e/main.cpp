#include <boost/multiprecision/gmp.hpp>
#include <boost/strong_typedef.hpp>
#include <iostream>

namespace XX {
    BOOST_STRONG_TYPEDEF(boost::multiprecision::mpz_int, Integer);

	std::ostream& operator<<(std::ostream& os, Integer const&) {
		return os << "XX overload";
	}
}

int main()
{
	boost::multiprecision::mpz_int a(0);
	XX::Integer b;

	std::cout << a << "\n";
	std::cout << b << "\n";
}
