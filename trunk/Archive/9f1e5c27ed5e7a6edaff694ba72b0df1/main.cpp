#include <string>
#include <vector>

#include <annex/type_traits.hpp>
using namespace annex;

template<int R> struct rank: rank<R+1> {};
template<> struct rank<9> {};

constexpr rank<0> select_overload {};

template<typename T, EnableIf<std::is_floating_point<Unqualified<T>>>...>
void foo(T const&, rank<0>);

template<typename T, EnableIf<std::is_copy_constructible<Unqualified<T>>>...>
void foo(T const&, rank<1>);

template<typename T, EnableIf<Not<std::is_copy_constructible<Unqualified<T>>>>...>
void foo(T const&, rank<1>);

template<typename T>
auto foo(T&& t) -> decltype(foo(std::forward<T>(t), select_overload))
{ return foo(std::forward<T>(t), select_overload); }

int main()
{
    foo(42);
}