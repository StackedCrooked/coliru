#include <type_traits>

template <typename T>
struct ClassName
{
  some_method()
  {
      static_assert(std::is_floating_point<T>(), "this one only for floats");
  }
};

int main()
{
  ClassName<double> d;
  ClassName<int> i;
}