struct foo_t {};

struct base
{
  void fun(unsigned) {}
};

#include <utility> // std::forward
struct decorator
{
  base b;

  template <typename... Args>
  auto
  fun(Args&&... args)
    -> decltype(b.fun(std::forward<Args>(args)...))
  {
    return b.fun(std::forward<Args>(args)...);
  }
};

struct decorated : decorator
{
  using decorator::fun;
  void fun(const foo_t&) {}
};

int main()
{
  decorated d;
  d.fun(foo_t{});
}