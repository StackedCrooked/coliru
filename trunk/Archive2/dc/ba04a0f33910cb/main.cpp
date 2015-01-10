#include <iostream>
#include <array>
using namespace std;

//array<array<int,1>,5> f() { return {array<int,1>{1},array<int,1>{2},array<int,1>{3},array<int,1>{4},array<int,1>{5}}; }
array<array<int,1>,5> f() { return { {{ 1 },{ 2 },{ 3 },{ 4 },{ 5 }} }; }

int main()
{
    const auto& v = f()[3];
    cout << v[0] << endl;
}
