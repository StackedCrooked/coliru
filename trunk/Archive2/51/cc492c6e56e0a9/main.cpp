#include <functional>
#include <utility>
#include <iostream>
#include <functional>
using namespace std;

// For generic types that are functors, delegate to its 'operator()'
template<typename... Args, class T>
auto make_function(T&& t) -> std::function<decltype(std::declval<T>()(std::declval<Args>()...))(Args...)> 
{return {std::forward<T>(t)};}

template<typename... Args, typename ReturnType>
auto make_function(ReturnType(*p)(Args...)) -> std::function<ReturnType(Args...)> 
{return {p};}

template<typename ClassType, typename ReturnType, typename... Args>
std::function<ReturnType(ClassType,Args...)> make_function(ReturnType(ClassType::*p)(Args...)) {return std::function<ReturnType(ClassType,Args...)>(p);}

// testing

int foo(int x, int y, int z) { return x + y + z;}

int main ()
{
  using namespace std::placeholders;
  int first = 4;
  auto f0 = make_function(foo);
  auto f1 = make_function<int,int,int>([](int x, int y, int z) { return x + y + z;});
  auto f2 = make_function<int,int>([=](int y, int z) { return first + y + z;});
  auto f3 = make_function<int,int,int>(std::bind(foo,_1,_2,_3));
  return 0;
}