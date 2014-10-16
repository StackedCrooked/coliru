#include <tuple>
#include <iostream>

int main() {
    std::cout << sizeof(std::tuple<double,double,bool>) << '\n';
    std::cout << (sizeof(std::tuple<double,double,bool>) * 700 * 574);
}