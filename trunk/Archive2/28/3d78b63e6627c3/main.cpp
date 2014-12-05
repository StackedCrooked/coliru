#include <iostream>
#include <type_traits>

int foo = 42;
int const& bar() { return foo; }

int main()
{
    auto a = bar();
    decltype(auto) b = bar();
    
    static_assert(std::is_same<decltype(a), int>::value, "a");
    static_assert(std::is_same<decltype(b), int const&>::value, "b");
}
