#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <boost/optional.hpp>

std::pair<int, int> foo() {
    if(42) {
        return std::make_pair(1,2);
    }
    throw std::logic_error("Oh my god");
}

int main() {
    try {
        std::pair<int, int> p = foo();
        int a = p.first;
        int b = p.second;
        std::cout << a << ' ' << b;
    } catch (std::logic_error const& e) {
        std::cerr << e.what();
    }
}