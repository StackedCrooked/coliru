#include <iostream>

struct S
{
    void member() {}
};

using Sptr = void (S::*)();

void take(Sptr &&p)
{
    std::cout << "R\n";
}

void take(Sptr &p)
{
    std::cout << "L\n";
}

int main()
{
    take(&S::member);
    auto f = &S::member;
    take(f);
}