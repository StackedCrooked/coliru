#include <iostream>
#include <string>
#include <tuple>
using namespace std;


struct Foo : tuple<int,string> {
    int& a;
    string& b;
    
    Foo(int a, string b) :
        tuple{a, b},
        a{get<0>(*this)}, b{get<1>(*this)}
    {}
};

int main()
{
    Foo const foo(0, "bar");
    
    long long a;
    string b;
    
    tie(a, b) = foo;
    cout << a << ' ' << b << '\n';
}
