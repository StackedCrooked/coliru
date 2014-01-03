#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>
#include <functional>
#include <string>
#include <typeinfo>

auto main() {
    auto i = new auto(1);
    std::cout << typeid(i).name();
	return 0;
}