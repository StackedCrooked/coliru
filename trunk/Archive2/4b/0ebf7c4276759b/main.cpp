#include <iostream>
#include <string>
#include <tuple>
using namespace std;


struct Foo : tuple<const int&,const string&> {
    int a;
    string b;
    
    Foo(int a, string b) :
        tuple{std::tie(this->a, this->b)},
        a{a}, b{b}
    {}
};

int main()
{
    const Foo foo(0, "bar");
    
    long long a;
    string b;
    
    tie(a, b) = foo;
    cout << a << ' ' << b << '\n';
}
