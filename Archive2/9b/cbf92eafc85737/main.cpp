#include <iostream>

using namespace std;

auto x(int n)
{
    return [n](int i) -> int { return n * i; };
}

auto main() -> int
{
    auto x2 = x(2);
    cout << x2(10) << endl;
    return 0;
}