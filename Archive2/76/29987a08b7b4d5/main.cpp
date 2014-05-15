#include <iostream>

struct MoreDouble
{
   operator double() { return 42.5; }
};

void foo(double x)
{
   std::cout << x << '\n';
}

int main()
{
   MoreDouble md;
   foo(md);
}