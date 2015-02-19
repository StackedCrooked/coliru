#include <type_traits>

template<typename F>
auto call1(F const& f) -> typename std::result_of<decltype(f)()>::type
{
  return f();
}

template<typename F>
auto call2(F const& f) -> decltype(f())
{
  return f();
}

auto call3(const auto& f) -> typename std::result_of<decltype(f)()>::type
{
  return f();
}

int main()
{
  call1([] { return 0; });
  call2([] { return 0; });
//  call3([] { return 0; });
}
