#include <iostream>
#include <type_traits>

auto && cin = std::cin;
auto && cou = std::cout;

int main()
{
    int n = 601187;
    cou << (cou << (cin >> n));
}
