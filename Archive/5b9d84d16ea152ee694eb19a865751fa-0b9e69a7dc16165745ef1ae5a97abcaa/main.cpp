#include <iostream>

struct h
{
    h(int n) : n(-n) {}
    operator int() { return n; }
    int n;
};

template<typename T>
auto f(T x)
{
    return h(x);
}

int main()
{
    std::cout << f(f(42)) << std::endl;
}
