#include <cassert>
#include <iostream>
#include <string>
using std::string;
#include <boost/optional.hpp>
using boost::optional;

optional<float> foo(int i) {
    if (i >= 0)
			return optional<float>(42.1);
	else
			return optional<float>();
}

int main() {


	auto x = foo(-1);
	assert(static_cast<bool>(x) == false);

	auto y = foo(1);
	assert(static_cast<bool>(y) == true);
	assert(y == 42.1f);

	std::cout << "all tests passed!" << std::endl;

}
