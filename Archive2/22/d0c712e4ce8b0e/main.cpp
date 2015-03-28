#include <memory>
#include <iostream>

using namespace std;

constexpr unsigned int factorial(unsigned int i)
{
    return (i > 1) ? i * factorial(i - 1) : 1;
}

auto answer = factorial(12);

int main()
{
    cout << "Here it is, computed at compile-time: " << answer;
    return 0;
}