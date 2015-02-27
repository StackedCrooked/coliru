#include <iostream>
#include <locale>
#include <sstream>

struct X
{
    X() { }
    X(X const&) { std::cout << "copy\n"; }
    X(X&&) { std::cout << "move\n"; }
    X(int) { }
};

void h(X) {}
 
int main()
{
    X x;
    h(x);
    h(5);
}