#include <cassert>
struct X {};
struct Y : X { virtual ~Y() = default; };
struct W : X { virtual ~W() = default; };
struct V { virtual ~V() = default; };
struct Z : Y, V, W { };

int main()
{
    V * something = new Z();
    X* x = dynamic_cast<Y*>(something);
    assert(x);
    X* y = dynamic_cast<X*>(something);
    assert(!y);
}