#include <tuple>

#include <iostream>

int main()
{
    std::tuple<int, double> t {}; // calls constexpr tuple();
    std::get<0>(t) = 17;
    std::cout << std::get<0>(t);
}
