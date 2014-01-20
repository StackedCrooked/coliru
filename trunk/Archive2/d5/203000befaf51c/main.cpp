#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <boost/optional.hpp>

boost::optional<std::pair<int, int>> foo() {
    if(1) {
        return std::make_pair(1,2);
    }
    return {};
}

int main() {
    auto p = foo();
    if (p) {
        int a = p->first;
        int b = p->second;
        std::cout << a << ' ' << b;
    } else {
        std::cerr << "Oh my god";
    }
}