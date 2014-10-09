#include <tuple>
#include <string>
#include <iostream>
#include <utility>


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

    const Foo c(0, "bar");
    std::get<0>(c) = 42;
}