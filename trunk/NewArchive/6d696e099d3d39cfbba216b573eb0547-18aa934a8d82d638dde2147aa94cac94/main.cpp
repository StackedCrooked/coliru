#include <iostream>

struct X
{
    X()    { std::cout << "X()\n";    }
    X(int) { std::cout << "X(int)\n"; }
};

const int answer = 42;

int main()
{
    X(answer);
}