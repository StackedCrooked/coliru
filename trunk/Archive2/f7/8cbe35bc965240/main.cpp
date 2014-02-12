#include <functional>
#include <utility>
#include <iostream>
#include <functional>
using namespace std;

// For generic types that are functors, delegate to its 'operator()'
template <typename T>
struct function_traits
  : public function_traits<decltype(&T::operator()(1, 2, 3))>
{};

// for pointers to member function
template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const> {
  enum { arity = sizeof...(Args) };
  typedef function<ReturnType (Args...)> f_type;
};

// for pointers to member function
template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) > {
  enum { arity = sizeof...(Args) };
  typedef function<ReturnType (Args...)> f_type;
};

// for function pointers
template <typename ReturnType, typename... Args>
struct function_traits<ReturnType (*)(Args...)>  {
  enum { arity = sizeof...(Args) };
  typedef function<ReturnType (Args...)> f_type;
};

template <typename L> 
static typename function_traits<L>::f_type make_function(L l){
  return (typename function_traits<L>::f_type)(l);
}
// testing

int foo(int x, int y, int z) { return x + y + z;}

int main ()
{
  using namespace std::placeholders;

  auto f0 = make_function(foo);
  auto f1 = make_function([](int x, int y, int z) { return x + y + z;});

    auto f2 = make_function(std::bind(foo, _1, _2, _3));
  return 0;
}