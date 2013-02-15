#include <type_traits>

template<class T>
auto f(T& v)
  -> decltype(typename std::enable_if<std::is_same<decltype(v.foo()), void>::value, int>::type(), v)
{ return v; }

template<class T>
auto f(T& v)
  -> decltype(typename std::enable_if<std::is_same<decltype(v.bar()), void>::value, int>::type(), v)
{ return v; }

int main(){
}