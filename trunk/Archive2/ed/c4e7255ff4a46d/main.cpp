#include <iostream>
#include <chrono>
#include <unistd.h>
using namespace std;

struct Foo {
    Foo() = delete;
    int foo();
};

int main()
{
    decltype(declval<Foo>().foo()) i;
    i;
}