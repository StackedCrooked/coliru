#include <type_traits>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>
#include <iostream>

class A {
 public:
  using value_type = unsigned int;

  template <class T>
  explicit A(T x): x_(boost::numeric_cast<T>(x)) { // can be check in debug only
    static_assert(std::is_integral<T>::value, "T must be integral");
  }

 private:
  value_type x_;
};

int main()
{
  std::cout << "test good" << std::endl;
  A ok(5);
  
  std::cout << "test catch negative" << std::endl;
  try {
    A bad(-5);
  }
  catch (std::bad_cast&) {
    std::cout << "catched" << std::endl;
  }
  
  std::cout << "test catch truncate" << std::endl;
  try {
    A bad(0xffffffffffffull);
  }
  catch (std::bad_cast&) {
    std::cout << "catched" << std::endl;
  }
}
