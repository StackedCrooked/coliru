#include <iostream>
using namespace std;

int Foo() { cout << "func\n"; }

struct Foo
{
    Foo() { cout << "class\n"; }
};

int main()
{
    Foo();
}