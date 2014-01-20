#include <type_traits>
#include <iostream>

struct X
{
    X() = default;
    X(X&) { std::cout << "hello!\n"; }
    X(X const&) = default;
};

struct Y
{
    X x;
};

static_assert(not std::is_trivial<X>{}, "X is trivial");
static_assert(std::is_trivial<Y>{}, "Y is not trivial");
static_assert(std::is_standard_layout<Y>{}, "Y is not standard-layout");
static_assert(std::is_pod<Y>{}, "Y is not POD");

int main()
{}