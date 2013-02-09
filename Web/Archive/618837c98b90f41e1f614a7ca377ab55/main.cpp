#include <cassert>

#include <boost/phoenix/phoenix.hpp>

struct Foo {
    int i;
};

struct Bar {
    Foo foo;
};

int main()
{
    using namespace boost::phoenix::placeholders;
    Bar b;
    auto member = ((&arg1)->*&Bar::foo)->*(&Foo::i);
    int& i = member(b);
    assert( &i == &b.foo.i );
}