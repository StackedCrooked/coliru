#include <memory>
#include <type_traits>
#include <iostream>

class A {
  template<class T>
  struct anti_friend : T {
    template<class... Ts>
    anti_friend (Ts&&... args) : T (std::forward<Ts> (args)...) { }
  };

  A (int x) : _value {x} { }

  int _value;

  public:
    static std::unique_ptr<A> fooz () {
      return std::make_unique<A> (anti_friend<A> (42));
    }

    std::unique_ptr<A> copy () const {
      return std::make_unique<A> (anti_friend<A> (*this));
    }

    int value () const {
      return _value;
    }
};

int main () {
  auto x = A::fooz ();
  auto y = x->copy ();

  std::cout << x.get () << " " << x->value () << std::endl;
  std::cout << y.get () << " " << y->value () << std::endl;
}