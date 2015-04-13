#include <functional> // for std::function
#include <iostream>

// example functions
void func(int i)
{
  std::cout << "Integer: " << i << ".\n";
}
int gunc(int i)
{
  int result = i+1;
  std::cout << "+Integer:" << result << ".\n";
  return result;
}

// general non-restrictive template
template<typename Function, typename Parameter>
void call_twice(Function f, Parameter p)
{
  f(p);
  f(p);
}
// Restrict signature to void(int), but the return value can be anything: it will be ignored
void call_thrice(std::function<void(int)> f, int p)
{
  f(p);
  f(p);
  f(p);
}
// Restrict signature to int(int), to exclude func
void call_four_times(std::function<int(int)> f, int p)
{
  f(p);
  f(p);
  f(p);
  f(p);
}

int main()
{
  call_twice(func, 1); // instantiates void call_twice(void (*)(int), int)
  call_twice(gunc, 1); // instantiated void call_twice(int (*)(int), int)
                     // Note I do not write the explicit types of func and gunc in the above comments, they're not important!

  call_thrice(func, 10); // converts func to a std::function<void(int)>
  call_thrice(gunc, 10); // return value can be ignored, so int(int) is convertible to void(int)
  
  //call_four_times(func, 100); // will fail to compile: cannot convert a function of signature void(int) to one with signature int(int)
  call_four_times(gunc, 100); // converts gunc to std::function<int(int)>
}