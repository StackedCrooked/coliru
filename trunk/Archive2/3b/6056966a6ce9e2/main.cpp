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
    cout << a << ' ' << b << '\n';
    
    tie(a, b) = X{};
    cout << a << ' ' << b << '\n';
    
    tie(a, b) = Y{5};
    cout << a << ' ' << b << '\n';
}
