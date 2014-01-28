#include <iostream>

struct foo
{
    foo(unsigned i) : i(i) {}
    unsigned i;
};

int main()
{
    foo f(-1);
}
