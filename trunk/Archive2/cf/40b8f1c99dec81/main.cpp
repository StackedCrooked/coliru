#include <functional>
#include <iostream>
#include <string>

// This is the function I'd like to have working:
template <class T, typename RETURN_TYPE, typename... Arguments, typename... Args>
std::function<RETURN_TYPE()> obj_bind(RETURN_TYPE (T::*in_fun)(Arguments...), T & obj, Arguments... params)
{
  return std::bind( std::mem_fn(in_fun), std::ref(obj), params...);
}

int main()
{
  // Standard use of push_back member function (our test case):
  std::string test_obj = "Test 1: ";
  test_obj.push_back('A');
  std::cout << test_obj << std::endl;

  // But I'd like to use this instead:
  auto test_fun = obj_bind( &std::string::push_back, test_obj, 'C');

  test_obj = "Test 2: ";
  test_fun();
  std::cout << test_obj << std::endl;
}
