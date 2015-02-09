#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>

struct Foo
{
    Foo() {}
    int bar = 5;  
};

int
main()
{
    boost::optional<Foo> foo;
    assert(!foo);
    foo = boost::in_place();
    assert(foo);
}