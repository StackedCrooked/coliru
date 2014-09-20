#include <cassert>

struct Base {};
struct Derived : Base {};

int main()
{
    Base obj;
    assert(!dynamic_cast<Derived&>(obj));
}
