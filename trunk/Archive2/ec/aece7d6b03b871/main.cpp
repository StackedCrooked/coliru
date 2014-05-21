#include <iostream>

constexpr unsigned floorlog2(unsigned x)
{
    return x < 2 ? x : 1+floorlog2(x >> 1);
}

int main()
{
    using namespace std;
    constexpr unsigned a = floorlog2(1024);
    cout << a << endl;
}
