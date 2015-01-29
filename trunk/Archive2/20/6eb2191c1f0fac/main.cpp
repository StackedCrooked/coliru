#include <iostream>

struct X
{
    int a = 0;
    float b = 0;
};

template <typename Callable>
void for_all_x (X &x, Callable &&callable)
{
    callable (x.a);
    callable (x.b);
}

int main()
{
    X x;
    for_all_x (x, [] (auto &thing) { thing += 1; });
    std::cout << x.a << std::endl;
}
