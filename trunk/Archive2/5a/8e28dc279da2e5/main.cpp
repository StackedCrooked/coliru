#include <functional>
#include <iostream>

struct X{ virtual void operator()() = 0; };
struct Y : X{ void operator()() override { std::cout << "operator()\n"; } };

int main()
{
    Y y;
    std::reference_wrapper<X> x(y);
    x();
}