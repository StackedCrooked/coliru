#include <iostream>
#include <cmath>
#include <limits>

int main() {
    double nan = std::numeric_limits<double>::quiet_NaN();
	std::cout << std::boolalpha << std::isnan(nan) << " == " << ! (nan == nan) << '\n';

}