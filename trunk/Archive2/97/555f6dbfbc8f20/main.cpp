#include <functional>
#include <utility>
#include <iostream>
#include <functional>
using namespace std;

// For generic types that are functors, delegate to its 'operator()'
template<typename ReturnType, typename... Args, class T>
std::function<ReturnType(Args...)> make_function(T&& t) {return std::function<ReturnType(Args...)>(std::forward<T>(t));}

template<typename ReturnType, typename... Args>
std::function<ReturnType(Args...)> make_function(ReturnType(*p)(Args...)) {return std::function<ReturnType(Args...)>(p);}

template<typename ClassType, typename ReturnType, typename... Args>
std::function<ReturnType(ClassType,Args...)> make_function(ReturnType(ClassType::*p)(Args...)) {return std::function<ReturnType(ClassType,Args...)>(p);}

// testing

int foo(int x, int y, int z) { return x + y + z;}

int main ()
{
  using namespace std::placeholders;

  auto f0 = make_function(foo);
  auto f1 = make_function<int,int,int,int>([](int x, int y, int z) { return x + y + z;});
  auto f2 = make_function<int,int,int,int>(std::bind(foo,_1,_2,_3)); //not OK
  return 0;
}