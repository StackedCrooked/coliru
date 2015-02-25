#include <iostream>
#include <string>
#include <vector>



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
    
struct Lalala {};

class Test {
    Foo f3 = Foo(Test);
};


int main()
{
    Foo f1('a', 1234);
    Foo f2(Lalala);
    
    Test test;
}
