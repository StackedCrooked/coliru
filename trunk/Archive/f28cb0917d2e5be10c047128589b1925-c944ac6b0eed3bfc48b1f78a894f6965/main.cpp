#include <functional>
#include <iostream>
#include <vector>

template<class T>
class SUBJECT_BASE
{
  std::vector<std::function<void(T)>> observers;

public:
  void do_notify () {
    for ( auto& obs : observers )
      obs( T{} );
  }
  
  void add_listener(std::function<void(T)> l) {
      observers.emplace_back(std::move(l));
  }
};

class X {};
class Y {};

int main ()
{
  SUBJECT_BASE<X> sub_a {};
  SUBJECT_BASE<X> sub_b {};
  SUBJECT_BASE<Y> sub_c {};

  sub_a.add_listener([](X){std::cout << "x from Subject_A" << std::endl;});
  sub_b.add_listener([](X){std::cout << "x from Subject_B" << std::endl;});
  sub_c.add_listener([](Y){std::cout << "y from Subject_C" << std::endl;});

  sub_a.do_notify();
  sub_b.do_notify();
  sub_c.do_notify();
}