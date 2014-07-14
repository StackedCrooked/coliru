#include <iostream>
#include <type_traits>

template <typename T>
class A
{
private:
  T a_;

public:
  A(T a) : a_(a) {}

  // 1. Return const reference to a_
  auto get() const -> decltype((a_))
  {
    return a_;
  }

  // 2. Return non-const reference to a_
  auto get() -> decltype((a_))
  {
    return a_;
  }
};

int main()
{
  A<int> a(3);
  static_assert(std::is_same<int&, decltype(a.get())>(), "");

  auto const& b = a;
  static_assert(std::is_same<int const&, decltype(b.get())>(), "");

  auto const& a1 = a.get(); // 1. Return const reference to a_
  //a1 = 4;  // Shouldn't compile
  std::cout << "Value of a = " << a.get() << std::endl;

  auto& a2 = a.get(); // 2. Return non-const reference to a_
  a2 = 5;
  std::cout << "Value of a = " << a.get() << std::endl;
}
