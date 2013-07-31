#include <iostream>

struct foo {};

template<typename T>
void bar(T&) { std::cout << "void bar(T&)\n"; }

template<typename T>
void bar(T&&) { std::cout << "void bar(T&&)\n"; }

int main()
{
    foo f;
    bar(f);
}
