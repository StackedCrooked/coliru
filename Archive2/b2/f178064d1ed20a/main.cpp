#include <iostream>
#include <memory>
#include <random>

struct A {
  virtual ~A() = default;
  virtual void doSomething() = 0;
};

struct B : A {
  ~B() override {
    std::cout << "~B\n";
  }
  void doSomething() override {
    std::cout << "I'm a B\n";
  }
  void setSomethingImplementationSpecific() {
    std::cout << "B::setSomethingImplementationSpecific\n";
  }
};

struct C : A {
  ~C() override {
    std::cout << "~C\n";
  }
  void doSomething() override {
    std::cout << "I'm a C\n";
  }
};

struct placement_deleter {
  template <typename T>
  void operator () (T* ptr) const {
    ptr->~T();
  }
};

inline void doSomething(A& a) {
  a.doSomething();
}

template <typename T>
using stack_ptr = std::unique_ptr<T, placement_deleter>;
template <typename...T>
using storage_t = typename std::aligned_union<0, T...>::type;

int main() {
  auto p = std::random_device{}() % 2;

  storage_t<B, C> storage;
  stack_ptr<A> a;
  if (p) {
    auto b = new (&storage) B();
    b->setSomethingImplementationSpecific();
    a.reset(b);
  } else {
    a.reset(new (&storage) C());
  }

  doSomething(*a);
}
