#include <boost/any.hpp>

struct foo
{
    foo() = default;
    foo(foo&&) = default;
};

struct bar
{
    bar() = default;
    bar(bar const&) = default;
};

int main()
{
    boost::any a1 = foo{};
    boost::any a2 = bar{};
}
