#include <iostream>
#include <iostream>
#include <iostream>

struct Bar1 {};
struct  Bar2 {};

class Foo
{
public:
    Foo(Bar1 * b1, Bar2 * b2) : bar1(b1), bar2(b2) {}
    template <typename T> T * GetData();
private:
    Bar1 * bar1;
    Bar2 * bar2;
};

template <> Bar1 * Foo::GetData<Bar1>() { return this->bar1;}
template <> Bar2 * Foo::GetData<Bar2>() { return this->bar2;}

int main()
{
    Foo * foo = new Foo(new Bar1(), new Bar2());
    Bar1 * b1 = foo->GetData<Bar1>();
    Bar2 * b2 = foo->GetData<Bar2>();
    b1 = nullptr;
    b2 = nullptr;
    delete foo;
}