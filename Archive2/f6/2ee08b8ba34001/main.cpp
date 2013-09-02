#include <cassert>
#include <cmath>
using std::sin;

struct A
{
    double sin() const { return 1.0; }
    double foo()
    {
        double x = 0.0;
        return sin(x);
    }
};

int main()
{
    A a;
    assert(a.foo() != 1.0);
}
