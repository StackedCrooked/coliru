// Stuff for Borgleader

#include <tuple>
#include <string>
#include <iostream>

template<typename Tuple>
auto add(const Tuple& tup) -> decltype(std::get<0>(tup) + std::get<1>(tup)) {
    return std::get<0>(tup) + std::get<1>(tup);
}

int main() {
    auto tup1 = std::make_tuple(std::string("one"),std::string("two"));
    auto tup2 = std::make_tuple(1.24f,0.121f);
    auto tup3 = std::make_tuple(1000,19281);
    std::cout << add(tup1) << '\n' << add(tup2) << '\n' << add(tup3);
}