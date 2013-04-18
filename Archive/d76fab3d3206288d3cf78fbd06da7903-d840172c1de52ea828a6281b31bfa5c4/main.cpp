#include <utility>
#include <type_traits>

template<typename T>
struct store {
   using value_type = T;
   
   store(T value): value(std::forward<T>(value)) {}
   
   T value;
};

template<typename T>
store<T> foo(T&& t)
{ return { std::forward<T>(t) }; }

#include <cassert>

int main()
{
   auto a = [] {};
   auto s = foo(std::move(a));
   static_assert( std::is_same<decltype(s)::value_type, decltype(a)&>(), "!" );
   assert( &s.value == &a );
}