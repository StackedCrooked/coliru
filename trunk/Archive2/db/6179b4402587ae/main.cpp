 namespace A
{
class a
{
private:
public:
a();

};
}
namespace A
{
class b
{
private:
public:
b();

};
}

#include <iostream>

A ::a::a()
{
    std::cout << "A\n";
}
A ::b::b()
{
    std::cout << "B\n";
}

int main()
{
    A::a a;
    A::b b;
}