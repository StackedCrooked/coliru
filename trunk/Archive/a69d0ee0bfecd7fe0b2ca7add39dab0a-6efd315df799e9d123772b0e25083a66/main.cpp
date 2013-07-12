#include <iostream>
#include <locale>
#include <iomanip>

void f() { }

template <typename... T>
void f(T... t)
{
    auto l = { ((std::cout << t), 0)... };
    f(t...);
}

int main()
{
    f(1, 2, 3, 4, 5);
}