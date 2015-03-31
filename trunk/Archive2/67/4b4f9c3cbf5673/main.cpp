#include <iostream>
#include <memory>
 
struct X
{
    X() { std::cout << "X()\n"; }
    X(X const&) { std::cout << "X(X const&)\n"; }
    X(X&&) { std::cout << "X(X&&)\n"; }
} v;

X&& f() { return std::move(v); }
 
int main()
{
    X a = X();
    X b = f();
    (void)a;(void)b;
}