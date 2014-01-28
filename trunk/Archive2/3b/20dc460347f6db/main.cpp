#include <iostream>
#include <string>

auto retfn(int times) {
    std::string kek;
	for (int i = 0; i < times; ++i) {
		kek += "heu";
	}
	return [=](std::string lel) {
		return kek + " " + lel;
	};
}

int main() {
	auto fn = retfn(10);
	std::cout << fn("C++");
}
