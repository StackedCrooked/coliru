#include <iostream>
#include <string>
#include <vector>

class c
{
public:
int f(int x);

};
int c::f(const int x)
{
    return 42;
}

int main()
{
    c i;
    i.f(5);
}
