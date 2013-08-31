#include <utility>
#include <type_traits>

template<int N>
struct dummy {};

template<typename T>
constexpr int Zero(T const&) { return 0; }

template<typename T>
constexpr std::true_type test(int, dummy<Zero([](T& t) { return t.bar; })> = {})
{ return {}; }

template<typename...>
constexpr std::false_type test(long) { return {}; }

struct foo { int bar; };

int main()
{
    static_assert( test<foo>(0), "" );
    static_assert( !test<int>(0), "" );
}