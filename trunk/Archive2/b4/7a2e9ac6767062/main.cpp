#include <iostream>

struct foo {};

void operator<<(int, foo) { std::cout << "what?\n"; }

int main()
{
    42 << foo();
}