#include <iostream>

using Id = unsigned;

struct foo
{
    foo(Id i) : i(i) {}
    Id i;
};

int main()
{
    foo f(-1);
}
