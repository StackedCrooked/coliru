#include <iostream>
#include <string>
#include <vector>


template<typename T>
class Foo {
public:
  template<typename... Ts>
  Foo(const Ts&... args) {
    std::cout << "Foo(...)" << std::endl;
  }

  
  Foo(int i) {
    std::cout << "Foo(int i)" << std::endl;
  }
};
    

int main()
{
    Foo<int> f1('a', 1234);
    Foo<int> f2(1234);
}
