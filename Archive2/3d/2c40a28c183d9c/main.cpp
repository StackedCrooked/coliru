#include <iostream>
#include <iomanip>

int main() { 
    double x = 7.0;
	unsigned char *xx = (unsigned char *)&x;

	std::cout << "7.0: ";

	for (size_t i=0; i<sizeof(x); i++) 
		std::cout << std::setw(2) << std::hex << (int)*xx++ << " ";

	std::cout << '\n';

	long long y = 7;
	unsigned char *yy = (unsigned char *) &y;

	std::cout << "7  : ";
	
	for (size_t i=0; i<sizeof(y); i++) 
		std::cout << std::setw(2) << std::hex << (int)*yy++ << " ";

	std::cout << '\n';
	
}
