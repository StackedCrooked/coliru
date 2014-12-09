#include <iostream>
void f(int& x)
{
     std::cout << "lvalue reference overload f(" << x << ")\n";
}
void f(const int& x)
{
     std::cout << "lvalue reference to const overload f(" << x << ")\n";
}
void f(int&& x)
{
     std::cout << "rvalue reference overload f(" << x << ")\n";
}
int main()
{
    int n = 1;
    const int x = 2;
    f(n); // calls f(int&)
    f(x); // calls f(const int&)
    f(3); // calls f(int&&)
          // would call f(const int&) if f(int&&) overload wasn't provided
}