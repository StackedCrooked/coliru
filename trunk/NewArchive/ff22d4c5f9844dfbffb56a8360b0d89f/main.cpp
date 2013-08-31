#include <type_traits>

template<class T, class U>
auto f(U& v)
  -> decltype(typename std::enable_if<std::is_same<decltype(v.foo()), T>::value, int>::type(), v)
{ return v; }

template<class T, class U>
auto f(U& v)
  -> decltype(typename std::enable_if<std::is_same<decltype(v.bar()), T>::value, int>::type(), v)
{ return v; }

int main(){
}