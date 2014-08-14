#include <type_traits>

template<int I>
struct A { static_assert(I > 0, "!"); using X = int; };

template<int, int* = nullptr, class = void>
void foo(...) {}

template<int I, typename std::enable_if< (I>0) >::type* = nullptr, class T = void>
auto foo(T) -> typename A<I>::X
{}

int main()
{
    foo<0,nullptr>(42); // works
	foo<0>(42);         // fails
}