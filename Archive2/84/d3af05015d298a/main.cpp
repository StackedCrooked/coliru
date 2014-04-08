#include <iostream>
#include <cmath>
#include <stdint.h>

using namespace std;

static bool my_isnan(double val) {
    union { double f; uint64_t x; } u = { val };
	return (u.x << 1) > 0x7ff0000000000000u;
}

int main() {
	cout << std::isinf(std::log(0.0)) << endl;
	cout << std::isnan(std::sqrt(-1.0)) << endl;
	cout << my_isnan(std::sqrt(-1.0)) << endl;

	return 0;
}

