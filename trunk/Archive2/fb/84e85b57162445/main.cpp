#include <cassert>
#include <type_traits>
#include <iostream>
#include <stdexcept>

template<typename Func>
auto WrapExceptions(Func&& f)
    -> typename std::result_of<Func()>::type
{
  try
  {
    return f();
  }
  catch(std::exception const &e)
  {
    std::cout << "Caught exception: " << e.what() << '\n';
    return typename std::result_of<Func()>::type{};
  }
}

int main()
{
    std::cout << WrapExceptions([]{ return std::string("lambda1"); }) << '\n';
    std::cout << WrapExceptions([]() -> std::string{ throw std::runtime_error("lambda2"); }) << '\n';
}
