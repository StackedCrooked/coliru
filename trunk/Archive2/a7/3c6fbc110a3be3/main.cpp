#include <functional>

#include <boost/make_shared.hpp>

struct foo {
    void bar() {}
};

int main()
{
    auto x = boost::make_shared<foo>();
    auto f = std::bind(&foo::bar, std::move(x));
    f();
}