#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
 
int main()
{
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
 
    std::sort(s.begin(), s.end());
    for (int a : s) {
        std::cout << a << " ";
    }
    std::cout << '\n';
 
    std::sort(s.begin(), s.end(), std::greater<int>());
    for (int a : s) {
        std::cout << a << " ";
    }
    std::cout << '\n';
}