#include <string>
#include <typeinfo>
#include <iostream>
#include <cmath>
#include <cstddef>

int to_int(std::string s) {
    if (s.empty()) throw std::bad_cast{};
    int i = 0;
    for (std::size_t j = s.size() - 1; j < s.size(); --j) {
        if (s[j] < '0' || s[j] > '9') throw std::bad_cast{};
        i += (s[j] - '0') * std::pow(10, j);
    }
    return i;
}

int main() {
    std::cout << to_int("12345") << '\n';
}
