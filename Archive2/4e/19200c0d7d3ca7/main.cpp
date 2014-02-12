#include <iostream>
enum foo { y };
//class we're trying to generate
template <int a, foo b>
class A
{
public:
  A()
  {
    std::cout << a << "," << (int)b << std::endl;

  }
};

#include <utility>
template <typename... B>
struct madscience_intitializer
{
  template <decltype(std::declval<B>()...)... Args>
  using ret_type = A<Args...>;
};

int main()
{
  madscience_intitializer<int, foo>::ret_type<1, foo::y> a;
}