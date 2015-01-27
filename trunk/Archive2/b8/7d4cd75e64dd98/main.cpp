#include <initializer_list>
#include <iostream>
#include <memory>

using namespace std;

template<class F, class...Ts> F for_each_arg(F f, Ts&&...a) {
  return (void)initializer_list<int>{(ref(f)((Ts&&)a), 0)...}, f;
  // why not return (void)initializer_list<int>{(f((Ts&&)a), 0)...}, f;
}

struct A { void foo() { std::cout << this << "->foo\n"; }; };
struct B : A {};
struct C : B {};

int main() {
    for_each_arg(&A::foo, A{}, B{}, C{}, std::make_unique<A>());
}
