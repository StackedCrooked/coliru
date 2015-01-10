#include <iostream>
#include <array>
using namespace std;

array<array<int,1>,5> f() { return { {{ 1 },{ 2 },{ 3 },{ 4 },{ 5 }} }; }

int main()
{
    const auto& v = f()[3];
    cout << v[0] << endl;
}
