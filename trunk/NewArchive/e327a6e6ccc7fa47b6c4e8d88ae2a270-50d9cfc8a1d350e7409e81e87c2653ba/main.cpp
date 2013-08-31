#include <iostream>
#include <map>

template <typename It>
auto f(It it) -> decltype(it->second) {
    return it->second;
}

int main() {
    std::map<int, char> x;

    x.insert(std::make_pair(42, 'a'));
    auto& ch = f(x.begin());
    ch = 'y';

    std::cout << x.find(42)->second << '\n';
}