#include <iostream>

double i = 10;

int f(const int&& j) { return j; }
int main()
{
    std::cout << f(i) << '\n';
}