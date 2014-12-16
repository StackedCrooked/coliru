#include <iostream>

struct X
{
    X(bool arg) { std::cout << arg << '\n'; }
};

int main() 
{
    int d = 7;
    X x{d};
}
