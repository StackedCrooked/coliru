#include <iostream>
#include <tuple>
using namespace std;

struct X : tuple<int,int> {
};

struct Y {
    int i;
    operator tuple<int&,int&>() {return tuple<int&,int&>{i,i};}
};

int main()
{
    int a, b;
    tie(a, b) = make_tuple(9,9);
    tie(a, b) = X{};
    tie(a, b) = Y{};
    cout << a << ' ' << b << '\n';
}
