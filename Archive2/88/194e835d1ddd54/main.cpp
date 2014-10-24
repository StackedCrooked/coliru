#include <type_traits>
#include <iostream>
#include <string>

template<typename T>
std::string type_helper() {
    std::string result(__PRETTY_FUNCTION__);
    return result.substr(result.find('=')+1);
}

template<typename T>
struct TYPE {};

#define TYPE(expr) TYPE<decltype(expr)>{};

template<typename T>
std::ostream& operator<<(std::ostream& o, TYPE<T>) {
    o << type_helper<T>();
    return o;
}

int main() {
    std::cout << TYPE(std::cout) << std::endl;
}
