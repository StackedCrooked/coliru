#include <utility>
#include <type_traits>

template<void*>
struct dummy {};

template<typename T>
constexpr T* addr(T&& t) { return &t; }

template<typename T>
constexpr void* instantiate(T*) { return nullptr; }

template<typename T>
constexpr std::true_type test(int, dummy<instantiate(false ? addr([](T& t) { return t.bar; }) : nullptr)> = {})
{ return {}; }

template<typename...>
constexpr std::false_type test(long) { return {}; }

struct foo { int bar; };

int main()
{
    static_assert( test<foo>(0), "" );
    static_assert( !test<int>(0), "" );
}