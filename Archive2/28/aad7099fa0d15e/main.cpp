#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
 
int main()
{
    std::pair<int, float> p1;
    std::cout << "Value-initialized: "
              << p1.first << ", " << p1.second << '\n';
 
    std::pair<int, double> p2(42, 0.123);
    std::cout << "Initialized with two values: "
              << p2.first << ", " << p2.second << '\n';
 
    std::pair<char, int> p4(p2);
    std::cout << "Implicitly converted: "
              << p4.first << ", " << p4.second << '\n';
 
    std::pair<std::complex<double>, std::string> p6(
                    std::piecewise_construct, 
                    std::forward_as_tuple(0.123, 7.7),
                    std::forward_as_tuple(10, 'a'));
    std::cout << "Piecewise constructed: "
              << p6.first << ", " << p6.second << '\n';
}