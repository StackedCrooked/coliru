#include <iostream>

struct test {
    test() = default;
	test& operator=(test const &) noexcept{
		std::cout << "operator =\n";
		return *this;
	}
};

bool operator>(test const &a, int const) noexcept{
	std::cout << "operator >\n";
	return false;
}

int main() {
	test a;
	a > 1 ? a : a = a;
	std::cout << "------------------------------\n";
	(a > 1 ? a : a) = a;

	return 0;
}