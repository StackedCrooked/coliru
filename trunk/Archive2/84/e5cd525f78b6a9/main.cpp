#include <iostream>
using namespace std;

struct Foo
{
    Foo()
    {
        cout << "default" << endl;
    }
    Foo(const Foo &)
    {
        cout << "copy" << endl;
    }
    Foo(Foo &&)
    {
        cout << "move" << endl;
    }
};

auto test(bool cond = true)
{
    Foo first, second;
    if(cond)
        return first;
    else
        return second;
}

int main()
{
    Foo x(test());
}
