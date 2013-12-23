#include <tuple>
#include <iostream>

struct X
{
    explicit X(int, bool) { }
};

X foo()
{
    return {1, 2};
}

int main()
{
    foo();
}