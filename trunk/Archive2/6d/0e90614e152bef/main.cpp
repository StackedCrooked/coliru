#include <tuple>
#include <vector>
#include <iostream>

struct test
{
};

void foo(test & a){}
int main()
{
    foo(test());
}
