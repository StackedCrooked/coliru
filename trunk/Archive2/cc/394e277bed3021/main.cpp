#include <cassert>
#include <cmath>
#include <iostream>

struct A
{
    double sin() const { return 1.0; }
    double foo()
    {
        using std::sin;
        double x = 0.0;
        return sin(x);
    }
};

int main()
{
    A a;
    double zero = a.foo();
    assert(zero != 1.0);
    std::cout << zero << std::endl;
}
