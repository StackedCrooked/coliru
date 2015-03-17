#include <type_traits>

#define ENABLE_IF_WELL_FORMED(X) typename = std::enable_if_t<std::is_same<decltype((X), void()), void>{}>

template<typename T>
struct base
{
    template<typename U = T, ENABLE_IF_WELL_FORMED(U::foo)>
    void bar() {}
};

struct derived : base<derived>
{
    template<typename U = derived, ENABLE_IF_WELL_FORMED(U::bar)>
    void foo() {}
};

int main()
{
    derived{}.bar();
}