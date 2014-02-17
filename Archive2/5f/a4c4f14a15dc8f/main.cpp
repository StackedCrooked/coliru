#include <functional>
#include <utility>
#include <iostream>
#include <functional>
using namespace std;

template<typename... Args, class T>
auto make_function(T&& t) 
    -> std::function<decltype(std::declval<T>()(std::declval<Args>()...))(Args...)> 
{return {std::forward<T>(t)};}

template<typename... Args, typename ReturnType>
auto make_function(ReturnType(*p)(Args...))
    -> std::function<ReturnType(Args...)> 
{return {p};}

template<typename... Args, typename ReturnType, typename ClassType>
auto make_function(ReturnType(ClassType::*p)(Args...)) 
    -> std::function<ReturnType(Args...)>
{return {p};}


// testing
struct A {
    short operator()() {return 3;}
};
struct B {
    int operator()(int) {return 0;}
    char operator()(char) {return 1;}
};

int foo(int x, int y, int z) { return x + y + z;}
int foos(char) { return 7;}
int foos(long) { return 8;}

int main ()
{
  using namespace std::placeholders;
  int first = 4;
  auto f0 = make_function(foo);
  auto f1 = make_function<char>(foos);
  auto f2 = make_function<int,int,int>([](int x, int y, int z) { return x + y + z;});
  auto f3 = make_function<int,int>([=](int y, int z) { return first + y + z;});
  auto f4 = make_function<int,int,int>(std::bind(foo,_1,_2,_3));
  auto f5 = make_function(A{});
  auto f6 = make_function<int>(B{});
  auto f7 = make_function<char>(B{});
  return 0;
}