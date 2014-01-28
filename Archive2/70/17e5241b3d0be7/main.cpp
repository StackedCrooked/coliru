#include <iostream>
#include <string>
#include <vector>
#include <boost/type_erasure/any.hpp>

namespace mpl = boost::mpl;
namespace te = boost::type_erasure;

template<class T>
struct fooable
{
    static void apply(T& arg) { arg.foo(); }
};

namespace boost { namespace type_erasure {
  template <class T, class Base>
  struct concept_interface<fooable<T>, Base, T> : Base
  {
    void foo()
    { call(fooable<T>(), *this); }
  };
}}

using A = te::any<boost::mpl::vector<
    te::copy_constructible<>,
    fooable<te::_self>,
    te::relaxed
>>;

struct B {
    void foo() {
        std::cout << "B::foo()\n";
    }
};

struct C {
    int foo(int i = 5) const {
        std::cout << "C::foo(" << i << ")\n";
        return i;
    }
};

struct D {
    void foo() {
        std::cout << "D::foo() " << x++ << "\n";
    }
    
    int x = 0;
};

void do_stuff(A a) {
    a.foo();
    a.foo();
}

int main() {
    do_stuff(B{});
    do_stuff(C{});
    do_stuff(D{});
}