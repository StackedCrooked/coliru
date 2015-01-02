#include <iostream>
#include <vector>

struct A { static bool init() { std::cout << "A\n"; return 0; } };
struct S { static bool init() { std::cout << "B\n"; return 0; } };

template<typename T>
struct dispatch
{
    dispatch() { T::init(); }
};

template<typename... Ts>
struct init_dispatch : std::integral_constant<bool, false>, dispatch<Ts>...
{
    init_dispatch() : dispatch<Ts>{}... {}
};

static bool const b = init_dispatch<A, S>{}.value;

int main()
{
}