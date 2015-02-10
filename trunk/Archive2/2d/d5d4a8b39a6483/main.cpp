#include <memory>
#include <type_traits>
#include <iostream>

class A { 
  private:
    class anti_friend { };

    A (int x) : _value (x) { } 
    A (A const&) = default;

    int _value;
    
  public:
    template<
      class    T,  
      class... Ts, 
      class =  decltype (anti_friend (T {}))
    > A (T, Ts&&... args)
      : A (std::forward<Ts> (args)...) // snap hack
    { } 

    static std::unique_ptr<A> fooz () {
      return std::make_unique<A> (anti_friend {}, 42);
    }   

    std::unique_ptr<A> copy () const {
      return std::make_unique<A> (anti_friend {}, *this);
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