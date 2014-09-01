#include <iostream>
#include <iomanip>

int main()
{
    unsigned int j = 10;
    int k = -42;

	// evaluate j - k. first apply 'usual arithmetic conversions' (in this case integral conversions)
	// http://en.cppreference.com/w/cpp/language/operator_arithmetic#Conversions
    
	// unsigned int and signed int have the same conversion rank
	// the unsigned operand's conversion rank is equal to the conversion rank of the signed operand,
	// so the signed operand is converted to the unsigned operand's type.
	unsigned int k_converted = k ;

	std::cout << std::hex << std::showbase << std::internal
	          << std::setw(30) << "value of j is "
	          << std::setw(10) << std::setfill('0') << j << '\n' << std::setfill(' ')
	          << std::setw(30) << "value of k_converted is "
	          << std::setw(10) << std::setfill('0') << k_converted << '\n' << std::setfill(' ')
	          << std::setw(30) << "value of j - k_converted is "
	          << std::setw(10) << std::setfill('0') << j - k_converted << '\n' << std::setfill(' ') ;

	std::cout << std::dec << std::setw(30) << "or decimal "
	          << std::setw(10) << std::setfill('0') << j - k_converted << '\n' ;

	std::cout << 1 - 2U << ' ' << '\n' ; // 4294967295 with 32-bit int (0xffffffff)
	std::cout << signed( 1 - 2U ) << '\n' ; // -1 (result converted to signed int)
}
