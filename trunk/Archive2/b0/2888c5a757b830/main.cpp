#include <iostream>
#include <ratio>
#include <cstdint>

template <std::intmax_t Num, std::intmax_t Denom>
std::ostream& operator<<(std::ostream& os, const std::ratio<Num,Denom> r) {
    os << r.num << "/" << r.den;
    return os;
}

int main() {
    std::cout << std::ratio<1,2>()    << std::endl;
    std::cout << std::ratio<4,2>()    << std::endl;
    std::cout << std::ratio<-10,-2>() << std::endl;
    // std::cout << std::ratio<1,0>()    << std::endl; // this doesn't compile!
}