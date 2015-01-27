#include <iostream>

struct X
{
    virtual void foo() {}
};

struct Y : X
{
    void foo() override {}
};

int main()
{
    Y y;
}