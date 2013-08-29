#include <type_traits>

template <typename T>
class ClassName
{
    // instance variables, etc..
 public:
  typename std::enable_if<std::is_floating_point<T>::value, void>::type 
  some_method()
  {
  }
};

int main()
{
  ClassName<double> d;
  ClassName<int> i;
}