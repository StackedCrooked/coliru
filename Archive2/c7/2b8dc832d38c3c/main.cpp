#include <utility>

struct foo
{
  auto bar() -> decltype(0)
  {
    return 0;
  }

  using bar_type = decltype(std::declval<foo>().bar());
};

int main()
{
  return 0;
}