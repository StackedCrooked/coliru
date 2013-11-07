#include <iostream>
#include <string>

namespace detail {
    struct Stringify {} _s;
}

using detail::_s;

template<typename T>
std::string operator,(T &&t, detail::Stringify &) {
    return std::to_string(std::forward<T>(t));   
}

int main() {
    int i = 5;
    std::cout << (i,_s);
}