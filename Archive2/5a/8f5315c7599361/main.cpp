#include <iostream>
#include <type_traits>

template<bool b, class c = void>
using enable_if_t = typename std::enable_if<b, c>::type;

struct foo_x { static void print() { std::cout<<"foo_x\n"; } };
struct foo_y { static void print() { std::cout<<"foo_y\n"; } };

template<int Version>
enable_if_t<(Version > 0), foo_x>
select_foo(...);

template<int Version>
enable_if_t<(Version > 2), foo_y>
select_foo(int, ...);

template<int Version>
using foo = decltype( select_foo<Version>(0, 0, 0, 0, 0) );

int main()
{
    foo<1>::print();
    foo<3>::print();
}