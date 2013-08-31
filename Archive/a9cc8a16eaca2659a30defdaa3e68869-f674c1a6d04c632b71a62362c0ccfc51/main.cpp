#include <iostream>


class A
{
protected:
    constexpr A() = default;
    ~A() = default;

    A(const A&) = delete;
};

class B
    : protected A
{
public:
    B() = default;
};

int main()
{
    B b;
}