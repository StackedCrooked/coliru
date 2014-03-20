#include <iostream>
#include <vector>
constexpr double square(double x) { return x*x; }

int main() 
{
    const int x=10;
    int y=20;
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
 
    for (int &i : v) // access by reference (const allowed)
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (auto i : v) // compiler uses type inference to determine the right type
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (int i : v) // access by value as well
        std::cout << i << ' ';
    constexpr double r = square(y);
 
    std::cout << '\n'<< square(y)<< '\n'<<r;
}