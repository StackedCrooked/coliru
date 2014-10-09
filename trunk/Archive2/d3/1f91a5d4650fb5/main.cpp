#include <iostream>
#include <string>
#include <tuple>
using namespace std;


struct Foo : tuple<int&,string&> {
    int a;
    string b;
    
    Foo(int a, string b) :
        tuple{std::tie(this->a, this->b)},
        a{a}, b{b}
    {}
};

int main()
{
    Foo foo(0, "bar");
    foo.a = 42;
    
    long long a;
    string b;
    
    tie(a, b) = foo;
    cout << a << ' ' << b << '\n';
}
