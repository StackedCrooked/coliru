#include <iostream>
#include <type_traits> // for std::result_of

template<typename Function, Function f>
struct A
{
  using function_type = Function;
  template<typename... ArgTypes>
  typename std::result_of<Function(ArgTypes...)>::type call(ArgTypes... args)
  {
    return f(args...);
  }
};

void func(int i) { std::cout << "Integer: " << i << ".\n"; }

int main()
{
  A<decltype(&func), func> a;
  a.call(42);
}