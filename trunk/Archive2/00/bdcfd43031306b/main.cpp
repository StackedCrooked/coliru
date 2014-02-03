#include <functional>

namespace N
{
  struct A
  {
    A(std::function<void()> f)
    {
    }
  };

  struct B
  {
    void method()
    {
    }
  };

  B b;

  A a(
    [] () -> void
    {
      b.method(); // C2065: 'b' : undeclared identifier
    }
  );
}

int main()
{
  return 0;
}