#include <utility>
#include <tuple>
#include <iostream>

int main()
{
    int a = 42, b = 50;
    int n;
    double c;
    std::tie(n, c) = std::make_tuple(2*a, b*.5);
    
    std::cout << n << ' ' << c << '\n';
}