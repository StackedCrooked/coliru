#include <functional>
#include <iostream>
#include <unordered_map>

template<class T>
class SUBJECT_BASE
{
  std::unordered_map<int, std::function<void(T)>> observers;
  int nextid = 0;

public:
  void do_notify ()
  {
    for ( auto& obs : observers )
      obs.second( T{} );
  }
  
  int add_listener(std::function<void(T)> l) {
      int id = ++nextid;
      observers.emplace(std::make_pair(id, std::move(l)));
      return id;
  }
  
  void remove_listener(int key) {
      observers.erase(key);
  }
};

class X {};
class Y {};

class Subject_A : public SUBJECT_BASE< X > {};
class Subject_B : public SUBJECT_BASE< X > {};
class Subject_C : public SUBJECT_BASE< Y > {};

int main ()
{
  Subject_A sub_a {};
  Subject_B sub_b {};
  Subject_C sub_c {};

  sub_a.add_listener([](X){std::cout << "x from Subject_A" << std::endl;});
  sub_b.add_listener([](X){std::cout << "x from Subject_B" << std::endl;});
  sub_c.add_listener([](Y){std::cout << "y from Subject_C" << std::endl;});

  sub_a.do_notify();
  sub_b.do_notify();
  sub_c.do_notify();
}