template<class D>
struct Base {
  friend constexpr int func (D);
};

template<class D>
struct impl : Base<D> {
  friend constexpr int func (D) {
    return {}; 
  }
};

struct A : Base<A> { constexpr A () = default; };
struct B : Base<B> { constexpr B () = default; };

template<class T>
constexpr int f (int N = noexcept (func (T{}))) {
  return N;
}
#include <iostream>

int main () {
  constexpr int m = f<A> (); 
  impl<A> {}; 
  constexpr int n = f<A> (); 

  std::cout << "RESULT: " << m << " " << n << std::endl;
}