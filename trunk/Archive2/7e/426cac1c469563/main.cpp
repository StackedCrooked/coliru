#include <iostream>
#include <tuple>


int main() {
    std::tuple<decltype(std::cout)&, decltype(std::clog)&> streams { std::cout, std::clog };
    std::get<0>(streams) << "cout\n";
    std::get<1>(streams) << "clog\n";
}