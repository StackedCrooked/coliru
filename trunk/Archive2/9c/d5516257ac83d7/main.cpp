#include <iostream>
#include <tuple>
using namespace std;

struct X : tuple<int,int> {
};

int main()
{
    int a, b;
    tie(a, b) = make_tuple(9,9);
    tie(a, b) = X{};
    cout << a << ' ' << b << '\n';
}
