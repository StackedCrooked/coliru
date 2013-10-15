#include <iostream>

struct A {};
auto operator == (A const&, A const&) { return "Hello World"; }

int main()
{
    std::cout << (A{} == A{}) << "\n";
}