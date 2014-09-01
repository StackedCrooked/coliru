#include <boost/multiprecision/gmp.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <iostream>

namespace XX {
    BOOST_STRONG_TYPEDEF(boost::multiprecision::mpz_int, Integer);

	std::ostream& operator<<(std::ostream& os, Integer const&) {
		return os << "XX overload";
	}
}

using namespace boost::multiprecision;

int main()
{
	mpz_int a(0);
	XX::Integer b(0);

	std::cout << a << "\n";
	std::cout << b << "\n";
}
