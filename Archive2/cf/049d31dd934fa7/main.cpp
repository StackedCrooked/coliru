#include <iostream>

struct die_loud
{
    int m;
    ~die_loud() { std::cout << "woot!" << m << "\n"; }
};
struct foo
{
    foo(die_loud const& p = {42}) : b(p) {}
    die_loud const& b;
};

int main()
{
    auto x = foo().b;
}