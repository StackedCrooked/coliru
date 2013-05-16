#include <iostream>
#include <utility>
#include <type_traits>


#define CLONEABLE(T) \
  virtual T* clone() const & { return new T(*this); } \
  virtual T* clone() && { return new T(std::move(*this)); }

  // XXX: the second one only if: std::is_move_constructible<T>::value == true ?


struct A {
  public:
    CLONEABLE(A)

    virtual ~A() { }
    virtual void fn() { std::cout << "A" << std::endl; }
};


struct B : public A {
  public:
    CLONEABLE(B)

    virtual ~B() { }
    virtual void fn() override { std::cout << "B" << std::endl; }
};


int main() {
  A* fst = new B;
  A* snd = fst->clone();

  fst->fn();
  snd->fn();

  // Yeah, I know about smart pointers. This is just an example.
  delete fst;
  delete snd;
}